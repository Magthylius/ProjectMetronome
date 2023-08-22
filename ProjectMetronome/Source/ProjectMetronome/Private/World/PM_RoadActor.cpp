// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PM_RoadActor.h"

#include "ProjectMetronome.h"
#include "World/PM_ActorPoolerSubsystem.h"

/* --- PUBLIC --- */

APM_RoadActor::APM_RoadActor()
{
	GetStaticMeshComponent()->SetEnableGravity(false);
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	GetStaticMeshComponent()->SetSimulatePhysics(false);

	PrimaryActorTick.bCanEverTick = true;
}

void APM_RoadActor::AddOwnedActor(AActor* OwnedActor)
{
	if (!IsValid(OwnedActor) || !OwnedActor->Implements<UPM_PoolableActorInterface>())
	{
		UE_LOG(LogPMWorld, Warning, TEXT("APM_RoadActor: Failed to add owned actor, is invalid."));
		return;
	}
	
	OwnedActors.Add(OwnedActor);
}

void APM_RoadActor::RemoveOwnedActor(AActor* OwnedActor)
{
	if (!IsValid(OwnedActor) || !OwnedActors.Contains(OwnedActor))
	{
		UE_LOG(LogPMWorld, Warning, TEXT("APM_RoadActor: Failed to remove owned actor, is invalid."));
		return;
	}

	OwnedActors.Remove(OwnedActor);
}

void APM_RoadActor::ReturnAllOwnedActors()
{
	if (UPM_ActorPoolerSubsystem* ActorPoolerSubsystem = GetWorld()->GetSubsystem<UPM_ActorPoolerSubsystem>())
	{
		for (auto OwnedActor : OwnedActors)
		{
			if (OwnedActor.IsValid())
				ActorPoolerSubsystem->ReturnActor(OwnedActor.Get());
		}

		OwnedActors.Empty();
	}
}

float APM_RoadActor::PerformChancedVeer()
{
	if (!bWantsToVeer && FMath::RandRange(0.f, 1.f) <= VeerChance)
	{
		bWantsToVeer = true;
		TargetPosition = GetActorLocation();
		TargetPosition.Y += (FMath::RandRange(VeerRange.X, VeerRange.Y) * (FMath::RandBool() ? 1.f : -1.f));
		return TargetPosition.Y;
	}

	return GetActorLocation().Y;
}

/* --- PROTECTED --- */

void APM_RoadActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (!bIsActive || !bWantsToVeer) return;
	const FVector NewLocation = FMath::Lerp(GetActorLocation(), TargetPosition, VeerSpeed * DeltaSeconds);
	SetActorLocation(NewLocation);
	
	/*if (FMath::IsNearlyEqual(GetActorLocation().Y, TargetPosition.Y, 0.1f))
	{
		SetActorLocation(TargetPosition);
		bWantsToVeer = false;
	}
	*/
	
	UE_LOG(LogPMWorld, Verbose, TEXT("APM_RoadActor [%s]: Performing veer from %f to %f."), *GetName(), GetActorLocation().Y, TargetPosition.Y);
}

void APM_RoadActor::SetActive(const bool bActiveState)
{
	bIsActive = bActiveState;
	SetActorHiddenInGame(!bActiveState);
	SetActorEnableCollision(bActiveState);
	SetActorTickEnabled(bActiveState);
	bWantsToVeer = false;
}

void APM_RoadActor::OnRoadSpawned()
{
	OriginalPosition = GetActorLocation();
	TargetPosition = OriginalPosition;

	UE_LOG(LogPMWorld, Verbose, TEXT("APM_RoadActor [%s]: Spawned on %s."), *GetName(), *OriginalPosition.ToString());

}

