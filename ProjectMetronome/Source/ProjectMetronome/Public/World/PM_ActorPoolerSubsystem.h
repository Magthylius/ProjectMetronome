// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PM_PoolableActorInterface.h"
#include "ProjectMetronome.h"
#include "Subsystems/WorldSubsystem.h"
#include "PM_ActorPoolerSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FPM_ActorInstanceContainer
{
	GENERATED_BODY()

public:
	FORCEINLINE bool HasInactiveActors() const { return !InactiveActors.IsEmpty(); }
	FORCEINLINE void AddInactiveActor(AActor* InactiveActor) { InactiveActors.Add(InactiveActor); }
	
	AActor* ActivateNewActor()
	{
		if (InactiveActors.Num() <= 0) return nullptr;
		const TObjectPtr<AActor> ActiveActor = InactiveActors[0];
		InactiveActors.RemoveAt(0);
		ActiveActors.Add(ActiveActor);
		Cast<IPM_PoolableActorInterface>(ActiveActor)->SetActive(true);
		return ActiveActor;
	}
	
	void DeactivateActor(AActor* ActorToDeactivate)
	{
		IPM_PoolableActorInterface* PoolableActor = Cast<IPM_PoolableActorInterface>(ActorToDeactivate);
		if (!ensure(PoolableActor))
		{
			UE_LOG(FPM_LogWorld, Warning, TEXT("FPM_ActorInstanceContainer: Tried to deactivate invalid actor."));
			return;
		}

		PoolableActor->SetActive(false);
		ActiveActors.Remove(ActorToDeactivate);
		InactiveActors.Add(ActorToDeactivate);
	}

private:
	TArray<TObjectPtr<AActor>> InactiveActors;
	TArray<TObjectPtr<AActor>> ActiveActors;
};

/**
 * 
 */
UCLASS()
class PROJECTMETRONOME_API UPM_ActorPoolerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	const bool bAllowOrphans = true;
	
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	bool CreateActor(const TSubclassOf<AActor> ActorClass, const uint8 Amount = 1);

	/* TODO: Does not account for derived classes. */
	template<typename TActor>
	TActor* RequestActor(const bool bAutoRefill = true)
	{
		AActor* RequestedActor = RequestActor(TActor::StaticClass(), bAutoRefill);
		return Cast<TActor>(RequestedActor);
	}
	
	AActor* RequestActor(const TSubclassOf<AActor> ActorClass, const bool bAutoRefill = true);
	
	bool ReturnActor(AActor* Actor);

private:
	TMap<TSubclassOf<AActor>, FPM_ActorInstanceContainer> ActorInstanceMap;
};
