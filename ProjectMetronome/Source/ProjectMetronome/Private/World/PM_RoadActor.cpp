// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PM_RoadActor.h"

#include "ProjectMetronome.h"
#include "World/PM_ActorPoolerSubsystem.h"

APM_RoadActor::APM_RoadActor()
{
	GetStaticMeshComponent()->SetEnableGravity(false);
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	GetStaticMeshComponent()->SetSimulatePhysics(false);
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

void APM_RoadActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void APM_RoadActor::SetActive(const bool bActiveState)
{
	bIsActive = bActiveState;
	SetActorHiddenInGame(!bActiveState);
	SetActorEnableCollision(bActiveState);
}

