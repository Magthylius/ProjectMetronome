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
}

void APM_RoadObstacleActor::OnActorWasHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse,	const FHitResult& Hit)
{
	const UWorld* CurrentWorld = GetWorld();
	if (!IsValid(CurrentWorld)) return;

	const APlayerController* PlayerController = CurrentWorld->GetFirstPlayerController();
	if (!IsValid(PlayerController)) return;

	APM_MainPawn* MainPawn = PlayerController->GetPawn<APM_MainPawn>();
	if (OtherActor == MainPawn)
	{
		MainPawn->TakeSlowDamage(GetSlowDamage());
		OnMainPawnHit(MainPawn);
		OnMainPawnCollided.Broadcast(this);
	}
}
