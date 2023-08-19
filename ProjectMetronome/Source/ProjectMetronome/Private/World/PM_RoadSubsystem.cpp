// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PM_RoadSubsystem.h"

#include "ProjectMetronome.h"
#include "World/PM_ActorPoolerSubsystem.h"

/* --- PUBLIC --- */

void UPM_RoadSubsystem::StartSubsystem(APM_MainPawn* InPlayerPawn, const FPM_RoadSubsystemInitData InitData)
{
	if (!ensure(IsValid(InitData.RoadClass)))
	{
		UE_LOG(FPM_LogWorld, Error, TEXT("UPM_RoadSubsystem: Invalid road class."));
		return;
	}

	PlayerPawn = InPlayerPawn;
	UPM_ActorPoolerSubsystem* PoolerSubsystem = GetWorld()->GetSubsystem<UPM_ActorPoolerSubsystem>();
	if (!ensure(IsValid(PoolerSubsystem)))
	{
		UE_LOG(FPM_LogWorld, Error, TEXT("UPM_RoadSubsystem: Invalid pooler subsystem."));
		return;
	}
	
	PoolerSubsystem->CreateActor(InitData.RoadClass, InitData.RoadTileAmount);
	
	RoadTileDistance = InitData.RoadTileDistance;
	for (int i = 0; i < InitData.RoadTileAmount; i++)
	{
		APM_RoadActor* RoadActor = PoolerSubsystem->RequestActor<APM_RoadActor>();
		RoadActor->SetActorLocation(FVector(0.f, RoadTileDistance * i, 0.f));
	}
}

/* --- PROTECTED --- */

void UPM_RoadSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bAllowObservation || !IsValid(PlayerPawn)) return;
	
}
