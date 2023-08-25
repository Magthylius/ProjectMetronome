// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PM_ActorPoolerSubsystem.h"

#include "World/PM_PoolableActorInterface.h"

bool UPM_ActorPoolerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

bool UPM_ActorPoolerSubsystem::CreateActors(const TSubclassOf<AActor> ActorClass, const uint8 Amount)
{
	if (!ensure(IsValid(ActorClass)) || !ensure(ActorClass->ImplementsInterface(UPM_PoolableActorInterface::StaticClass())))
	{
		UE_LOG(LogPMWorld, Error, TEXT("UPM_ActorPoolerSubsystem: Invalid actor class, failed to create actor."));
		return false;
	}
	
	UWorld* CurrentWorld = GetWorld();
	if (!ensure(IsValid(CurrentWorld)))
	{
		UE_LOG(LogPMWorld, Error, TEXT("UPM_ActorPoolerSubsystem: Invalid world, failed to create actor."));
		return false;
	}

	if (!ActorInstanceMap.Contains(ActorClass)) ActorInstanceMap.Add(ActorClass, FPM_ActorInstanceContainer());
	for (uint8 i = 0; i < Amount; i++)
	{
		AActor* SpawnedActor = CurrentWorld->SpawnActor(ActorClass);
		Cast<IPM_PoolableActorInterface>(SpawnedActor)->SetActive(false);
		ActorInstanceMap[ActorClass].AddInactiveActor(SpawnedActor);
	}
	
	return true;
}

AActor* UPM_ActorPoolerSubsystem::RequestActor(const TSubclassOf<AActor> ActorClass, const bool bAutoRefill)
{
	if (!ensure(IsValid(ActorClass)) || !ensure(ActorClass->ImplementsInterface(UPM_PoolableActorInterface::StaticClass())))
	{
		UE_LOG(LogPMWorld, Error, TEXT("UPM_ActorPoolerSubsystem: Invalid actor class, failed to request for actor."));
		return nullptr;
	}

	if (!ActorInstanceMap.Contains(ActorClass))
	{
		if (bAutoRefill) CreateActors(ActorClass);
		else return nullptr;
	}

	if (!ActorInstanceMap[ActorClass].HasInactiveActors())
	{
		if (bAutoRefill) CreateActors(ActorClass);
		else return nullptr;
	}

	AActor* RequestedActor = ActorInstanceMap[ActorClass].ActivateNewActor();
	Cast<IPM_PoolableActorInterface>(RequestedActor)->OnActorPoolRequested();
	return RequestedActor;
}

bool UPM_ActorPoolerSubsystem::ReturnActor(AActor* Actor)
{
	if (!IsValid(Actor)) return false;
	
	UClass* ActorClass = Actor->GetClass();
	if (!ActorInstanceMap.Contains(ActorClass))
	{
		if (bAllowOrphans) ActorInstanceMap.Add(ActorClass, FPM_ActorInstanceContainer());
		else return false;
	}

	Cast<IPM_PoolableActorInterface>(Actor)->OnActorPoolReturned();
	ActorInstanceMap[ActorClass].DeactivateActor(Actor);
	return true;
}
