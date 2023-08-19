// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PM_RoadSubsystem.h"

#include "ProjectMetronome.h"
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

	{ /* Initialize road to drive on. */
		ActorPoolerSubsystem->CreateActors(InitData.RoadClass, InitData.RoadTileAmount);
		for (int i = -2; i < InitData.RoadTileAmount - 2; i++)
		{
			APM_RoadActor* RoadActor = Cast<APM_RoadActor>(ActorPoolerSubsystem->RequestActor(InitData.RoadClass));
			const FVector Location = FVector::ForwardVector * InitData.RoadTileDistance * i;
			RoadActor->SetActorLocation(Location);
			RoadActors.Add(RoadActor);
		}
	}

	{ /* Pool obstacles. */
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
	if (!ensure(IsValid(PlayerPawn))) return -1.f;
	
	const int PlayerIndex = PlayerPawn->GetActorLocation().X / InitData.RoadTileDistance;
	return (OffsetIndex + PlayerIndex) * InitData.RoadTileDistance;
}

/* --- PROTECTED --- */

void UPM_RoadSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const UWorld* CurrentWorld = GetWorld();
	if (!bAllowObservation || !IsValid(PlayerPawn) || !IsValid(CurrentWorld)) return;

	{ /* Road scrolling system. */
		//! Road actors work in a queue system. That means the first one is always the oldest one.
		if (RoadActors.Num() <= 0) return;

		const float BackBuffer = PlayerPawn->GetActorLocation().X + InitData.RoadBackBuffer;
		APM_RoadActor* RoadActor = RoadActors[0].Get();

		if (RoadActor->GetActorLocation().X > BackBuffer) return;

		RoadActors.RemoveAt(0);
		ActorPoolerSubsystem->ReturnActor(RoadActor);

		APM_RoadActor* NewRoadActor = Cast<APM_RoadActor>(ActorPoolerSubsystem->RequestActor(InitData.RoadClass));
		NewRoadActor->SetActorLocation(FVector(GetQuantizedPosition(InitData.RoadFrontBufferIndex), 0.f, 0.f));
		RoadActors.Add(NewRoadActor);
	}

	{ /* Obstacle spawning system. We don't use a timer so we can set obstacle timing for ramping difficulty. */
		if (!bAllowObstacleSpawn || CurrentWorld->GetTimeSeconds() < NextObstacleSpawnTime) return;
		NextObstacleSpawnTime = GetWorld()->GetTimeSeconds() + InitData.ObstacleSpawnInterval;
		SpawnObstacle();
	}
}

/* --- PRIVATE --- */

void UPM_RoadSubsystem::SpawnObstacle()
{
	const TSubclassOf<APM_RoadObstacleActor> ObstacleClass = InitData.RoadObstacleTypes[FMath::RandRange(0, InitData.RoadObstacleTypes.Num() - 1)];
	
	APM_RoadObstacleActor* Obstacle = ActorPoolerSubsystem->RequestActor<APM_RoadObstacleActor>(ObstacleClass, true);
	if (!IsValid(Obstacle))
	{
		UE_LOG(LogPMWorld, Warning, TEXT("UPM_RoadSubsystem: Cannot spawn more obstacles, limit reached."));
		return;
	}
	Obstacle->OnMainPawnCollided.AddUObject(this, &UPM_RoadSubsystem::OnObstacleCollided);
	
	const APM_RoadActor* LastRoadActor = RoadActors.Last().Get();
	
	FVector SpawnLocation = LastRoadActor->GetActorLocation();
	SpawnLocation.X += FMath::RandRange(-InitData.ObstacleSpawnHalfRange.X, InitData.ObstacleSpawnHalfRange.X);
	SpawnLocation.Y += FMath::RandRange(-InitData.ObstacleSpawnHalfRange.Y, InitData.ObstacleSpawnHalfRange.Y);
	SpawnLocation.Z = InitData.RoadSurfaceLevel;

	Obstacle->SetActorLocation(SpawnLocation);
}

void UPM_RoadSubsystem::OnObstacleCollided(APM_RoadObstacleActor* ObstacleActor) const
{
	auto ReturnActorDelegate = [this, ObstacleActor]()
	{
		ActorPoolerSubsystem->ReturnActor(ObstacleActor);
	};
	
	ObstacleActor->OnMainPawnCollided.RemoveAll(this);
	FTimerHandle DisposableHandle;
	GetWorld()->GetTimerManager().SetTimer(DisposableHandle, ReturnActorDelegate, 3.f, false);
}
