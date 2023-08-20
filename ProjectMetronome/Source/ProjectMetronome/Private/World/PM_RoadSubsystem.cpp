// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PM_RoadSubsystem.h"

#include "ProjectMetronome.h"
#include "Shell/PM_ScoreSystem.h"
#include "World/PM_ActorPoolerSubsystem.h"

/* --- PUBLIC --- */

void UPM_RoadSubsystem::StartSubsystem(APM_MainPawn* InPlayerPawn, const FPM_RoadSubsystemInitData& InInitData)
{
	if (!ensure(IsValid(InInitData.RoadClass)))
	{
		UE_LOG(LogPMWorld, Error, TEXT("UPM_RoadSubsystem: Invalid road class."));
		return;
	}

	PlayerPawn = InPlayerPawn;
	InitData = InInitData;

	ActorPoolerSubsystem = GetWorld()->GetSubsystem<UPM_ActorPoolerSubsystem>();
	if (!ensure(ActorPoolerSubsystem.IsValid()))
	{
		UE_LOG(LogPMWorld, Error, TEXT("UPM_RoadSubsystem: Invalid pooler subsystem."));
		return;
	}

	{
		/* Initialize road to drive on. */
		ActorPoolerSubsystem->CreateActors(InitData.RoadClass, InitData.RoadTileAmount);
		for (int i = -2; i < InitData.RoadTileAmount - 2; i++)
		{
			APM_RoadActor* RoadActor = Cast<APM_RoadActor>(ActorPoolerSubsystem->RequestActor(InitData.RoadClass));
			const FVector Location = FVector::ForwardVector * InitData.RoadTileDistance * i;
			RoadActor->SetActorLocation(Location);
			RoadActors.Add(RoadActor);
		}
	}

	{
		/* Pool obstacles. */
		for (int i = 0; i < InitData.RoadObstacleTypes.Num(); ++i)
		{
			const TSubclassOf<APM_RoadObstacleActor> ObstacleClass = InitData.RoadObstacleTypes[i];
			ActorPoolerSubsystem->CreateActors(ObstacleClass, InitData.ObstaclePoolAmount);

			auto AllowObstacleSpawning = [this]
			{
				bAllowObstacleSpawn = true;
			};

			GetWorld()->GetTimerManager().SetTimer(ObstacleSpawnHandle, AllowObstacleSpawning, InitData.ObstacleStartSpawnDelay, false);
		}
	}

	bAllowObservation = true;
}

float UPM_RoadSubsystem::GetQuantizedPosition(const int OffsetIndex) const
{
	if (!ensure(IsValid(PlayerPawn)))
	{
		return -1.f;
	}

	const int PlayerIndex = PlayerPawn->GetActorLocation().X / InitData.RoadTileDistance;
	return (OffsetIndex + PlayerIndex) * InitData.RoadTileDistance;
}

/* --- PROTECTED --- */

void UPM_RoadSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const UWorld* CurrentWorld = GetWorld();
	if (!bAllowObservation || !IsValid(PlayerPawn) || !IsValid(GetWorld()))
	{
		return;
	}

	TickRoadScrolling();
	TickObstacleSpawning();
	TickObstacleScoring();
}

void UPM_RoadSubsystem::TickRoadScrolling()
{
	//! Road actors work in a queue system. That means the first one is always the oldest one.
	if (RoadActors.Num() <= 0)
	{
		return;
	}

	const float BackBuffer = PlayerPawn->GetActorLocation().X + InitData.RoadBackBuffer;
	APM_RoadActor* RoadActor = RoadActors[0].Get();

	if (RoadActor->GetActorLocation().X > BackBuffer)
	{
		return;
	}

	RoadActor->ReturnAllOwnedActors();
	RoadActors.RemoveAt(0);
	ActorPoolerSubsystem->ReturnActor(RoadActor);

	APM_RoadActor* NewRoadActor = Cast<APM_RoadActor>(ActorPoolerSubsystem->RequestActor(InitData.RoadClass));
	NewRoadActor->SetActorLocation(FVector(GetQuantizedPosition(InitData.RoadFrontBufferIndex), 0.f, 0.f));
	RoadActors.Add(NewRoadActor);

	//! Add all unowned obstacles to most recent road actor
	for (const TWeakObjectPtr<APM_RoadObstacleActor> Obstacle : UnownedRoadObstacles)
	{
		Obstacle->SetOwningRoad(NewRoadActor);
	}
	UnownedRoadObstacles.Empty();
}

void UPM_RoadSubsystem::TickObstacleSpawning()
{
	if (!bAllowObstacleSpawn || GetWorld()->GetTimeSeconds() < NextObstacleSpawnTime)
	{
		return;
	}
	NextObstacleSpawnTime = GetWorld()->GetTimeSeconds() + InitData.ObstacleSpawnInterval;
	SpawnObstacle();
}

void UPM_RoadSubsystem::TickObstacleScoring()
{
	for (int i = OncomingRoadObstacles.Num() - 1; i >= 0; i--)
	{
		TWeakObjectPtr<APM_RoadObstacleActor> RoadObstacle = OncomingRoadObstacles[i];

		//! Player pawn has passed obstacle
		if (RoadObstacle->GetDistance() < PlayerPawn->GetDistance())
		{
			OncomingRoadObstacles.Remove(RoadObstacle);
			FPM_ScoreSystem::NotifyObstaclePassed();
			UE_LOG(LogPMWorld, Verbose, TEXT("UPM_RoadSubsystem: Road obstacle '%s' passed at %f against %f."),
			       *RoadObstacle->GetName(), RoadObstacle->GetDistance(), PlayerPawn->GetDistance());
		}
	}
}

/* --- PRIVATE --- */

void UPM_RoadSubsystem::SpawnObstacle()
{
	const TSubclassOf<APM_RoadObstacleActor> ObstacleClass = InitData.RoadObstacleTypes[FMath::RandRange(
		0, InitData.RoadObstacleTypes.Num() - 1)];

	APM_RoadObstacleActor* Obstacle = ActorPoolerSubsystem->RequestActor<APM_RoadObstacleActor>(ObstacleClass, true);
	if (!IsValid(Obstacle))
	{
		UE_LOG(LogPMWorld, Warning, TEXT("UPM_RoadSubsystem: Cannot spawn more obstacles, limit reached."));
		return;
	}
	Obstacle->OnMainPawnCollided.AddUObject(this, &UPM_RoadSubsystem::OnObstacleCollided);

	FVector SpawnLocation = PlayerPawn->GetActorLocation();
	SpawnLocation.X += FMath::RandRange(-InitData.ObstacleSpawnHalfRange.X, InitData.ObstacleSpawnHalfRange.X) +
		InitData.ObstacleSpawnDistance;
	SpawnLocation.Y = FMath::RandRange(-InitData.ObstacleSpawnHalfRange.Y, InitData.ObstacleSpawnHalfRange.Y);
	SpawnLocation.Z = InitData.ObstacleSpawnHeight;

	APM_RoadActor* LastRoadActor = RoadActors.Last().Get();

	//! Obstacle will be before road actor center
	if (FMath::Abs(SpawnLocation.X - LastRoadActor->GetDistance()) <= InitData.ObstacleSpawnDistance * 0.5f)
	{
		Obstacle->SetOwningRoad(LastRoadActor);
	}
	else
	{
		UnownedRoadObstacles.Add(Obstacle);
	}

	Obstacle->SetActorLocation(SpawnLocation);
	Obstacle->AddActorLocalOffset(FVector::DownVector * InitData.ObstacleSpawnHeight, true);
	Obstacle->NotifyObstacleSpawned();
	OncomingRoadObstacles.Add(Obstacle);
}

void UPM_RoadSubsystem::OnObstacleCollided(APM_RoadObstacleActor* ObstacleActor) const
{
	//! NOTE: ObstacleActor handles its own detachment from owning road 
	ObstacleActor->OnMainPawnCollided.RemoveAll(this);
	ObstacleActor->StartReturnCountdown(ActorPoolerSubsystem.Get(), FPM_GameSettings::ObstacleReturnTime);
	FPM_ScoreSystem::NotifyObstacleHit();
}
