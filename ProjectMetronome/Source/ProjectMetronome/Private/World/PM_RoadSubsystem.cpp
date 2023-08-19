// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PM_RoadSubsystem.h"

#include "ProjectMetronome.h"
#include "Shell/PM_LogUtil.h"
#include "World/PM_ActorPoolerSubsystem.h"

/* --- PUBLIC --- */

void UPM_RoadSubsystem::StartSubsystem(APM_MainPawn* InPlayerPawn, const FPM_RoadSubsystemInitData& InInitData)
{
	if (!ensure(IsValid(InInitData.RoadClass)))
	{
		UE_LOG(FPM_LogWorld, Error, TEXT("UPM_RoadSubsystem: Invalid road class."));
		return;
	}

	PlayerPawn = InPlayerPawn;
	
	ActorPoolerSubsystem = GetWorld()->GetSubsystem<UPM_ActorPoolerSubsystem>();
	if (!ensure(ActorPoolerSubsystem.IsValid()))
	{
		UE_LOG(FPM_LogWorld, Error, TEXT("UPM_RoadSubsystem: Invalid pooler subsystem."));
		return;
	}
	
	ActorPoolerSubsystem->CreateActor(InInitData.RoadClass, InInitData.RoadTileAmount);
	
	RoadTileDistance = InInitData.RoadTileDistance;
	for (int i = -2; i < InInitData.RoadTileAmount - 2; i++)
	{
		APM_RoadActor* RoadActor = Cast<APM_RoadActor>(ActorPoolerSubsystem->RequestActor(InInitData.RoadClass));
		const FVector Location = FVector::ForwardVector * RoadTileDistance * i;
		RoadActor->SetActorLocation(Location);
		RoadActors.Add(RoadActor);
	}

	InitData = InInitData;
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

	if (!bAllowObservation || !IsValid(PlayerPawn)) return;

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
