// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PM_ActorPoolerSubsystem.h"

#include "ProjectMetronome.h"
#include "World/PM_PoolableActorInterface.h"

bool UPM_ActorPoolerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

bool UPM_ActorPoolerSubsystem::CreateActor(const TSubclassOf<AActor> ActorClass, const uint8 Amount)
{
	if (!ensure(IsValid(ActorClass)) || !ensure(ActorClass->ImplementsInterface(UPM_PoolableActorInterface::StaticClass())))
	{
		UE_LOG(FPM_LogWorld, Error, TEXT("UPM_ActorPoolerSubsystem: Invalid actor class, failed to create actor."));
		return false;
	}
	
	UWorld* CurrentWorld = GetWorld();
	if (!ensure(IsValid(CurrentWorld)))
	{
		UE_LOG(FPM_LogWorld, Error, TEXT("UPM_ActorPoolerSubsystem: Invalid world, failed to create actor."));
		return false;
	}
	
	if (!ActorInstanceMap.Contains(ActorClass)) ActorInstanceMap.Add(ActorClass, FPM_ActorInstanceContainer());
	for (uint8 i = 0; i < Amount; i++)
	{
		AActor* SpawnedActor = CurrentWorld->SpawnActor(ActorClass);
		ActorInstanceMap[ActorClass].InactiveActors.Enqueue(SpawnedActor);
	}
	
	return true;
}

AActor* UPM_ActorPoolerSubsystem::RequestActor(const TSubclassOf<AActor> ActorClass, const bool bAutoRefill)
{
	if (!ensure(IsValid(ActorClass)) || !ensure(ActorClass->ImplementsInterface(UPM_PoolableActorInterface::StaticClass())))
	{
		UE_LOG(FPM_LogWorld, Error, TEXT("UPM_ActorPoolerSubsystem: Invalid actor class, failed to request for actor."));
		return nullptr;
	}

	if (!ActorInstanceMap.Contains(ActorClass))
	{
		if (bAutoRefill) CreateActor(ActorClass);
		else return nullptr;
	}

	if (ActorInstanceMap[ActorClass].InactiveActors.IsEmpty())
	{
		if (bAutoRefill) CreateActor(ActorClass);
		else return nullptr;
	}
	
	return ActorInstanceMap[ActorClass].ActivateNewActor();
}

bool UPM_ActorPoolerSubsystem::ReturnActor(AActor* Actor)
{
	UClass* ActorClass = Actor->GetClass();
	if (!ActorInstanceMap.Contains(ActorClass))
	{
		if (bAllowOrphans) ActorInstanceMap.Add(ActorClass, FPM_ActorInstanceContainer());
		else return false;
	}

	ActorInstanceMap[ActorClass].DeactivateActor(Actor);
	return true;
}
