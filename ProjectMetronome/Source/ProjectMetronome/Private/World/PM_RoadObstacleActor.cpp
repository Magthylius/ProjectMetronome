// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PM_RoadObstacleActor.h"

APM_RoadObstacleActor::APM_RoadObstacleActor()
{
	OnActorHit.AddUniqueDynamic(this, &APM_RoadObstacleActor::OnActorWasHit);
}

void APM_RoadObstacleActor::SetActive(const bool bActiveState)
{
	bIsActive = bActiveState;
	SetActorHiddenInGame(!bActiveState);
	SetActorEnableCollision(bActiveState);
	ReturnHandle.Invalidate();
	bHasBeenCollided = false;
}

void APM_RoadObstacleActor::SetOwningRoad(APM_RoadActor* RoadActor)
{
	RoadActor->AddOwnedActor(this);
	OwningRoadActor = RoadActor;
}

void APM_RoadObstacleActor::StartReturnCountdown(UPM_ActorPoolerSubsystem* PoolerSubsystem, const float Countdown)
{
	if (Countdown < 0.f) return;
	GetWorld()->GetTimerManager().SetTimer(ReturnHandle, [this, PoolerSubsystem] { PoolerSubsystem->ReturnActor(this); }, Countdown, false);
	UE_LOG(LogPMWorld, Log, TEXT("APM_RoadObstacleActor: Has started return countdown."));
}

void APM_RoadObstacleActor::PerformRandomSpawnEffects()
{
	if (bWantsRandomSize)
	{
		FVector RandomSize;
		RandomSize.X = FMath::RandRange(MinRandomSize.X, MaxRandomSize.X);
		RandomSize.Y = FMath::RandRange(MinRandomSize.Y, MaxRandomSize.Y);
		RandomSize.Z = FMath::RandRange(MinRandomSize.Z, MaxRandomSize.Z);

		SetActorScale3D(OriginalScale * RandomSize);
	}

	if (bWantsRandomColor)
	{
		const int RandomColorIndex = FMath::RandRange(0, RandomColorRange.Num() - 1);
		OnSetColor(RandomColorRange[RandomColorIndex]);
	}
}

void APM_RoadObstacleActor::BeginPlay()
{
	Super::BeginPlay();
	OriginalScale = GetActorScale();
}

void APM_RoadObstacleActor::OnObstacleSpawned()
{

}

/* --- PROTECTED --- */

void APM_RoadObstacleActor::OnActorWasHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	const UWorld* CurrentWorld = GetWorld();
	if (!IsValid(CurrentWorld)) return;

	const APlayerController* PlayerController = CurrentWorld->GetFirstPlayerController();
	if (!IsValid(PlayerController)) return;

	APM_MainPawn* MainPawn = PlayerController->GetPawn<APM_MainPawn>();
	if (OtherActor == MainPawn && !bHasBeenCollided)
	{
		bHasBeenCollided = true;
		MainPawn->TakeSlowDamage(GetSlowDamage());

		//! Detach from owning road so it doesn't get returned to the pooler
		if (OwningRoadActor.IsValid()) //! TODO:
		{
			OwningRoadActor.Get()->RemoveOwnedActor(this);
			UE_LOG(LogPMWorld, Log, TEXT("APM_RoadObstacleActor: Self removed from owning actor."));
		}

		OnMainPawnHit(MainPawn);
		OnMainPawnCollided.Broadcast(this);
	}
}
