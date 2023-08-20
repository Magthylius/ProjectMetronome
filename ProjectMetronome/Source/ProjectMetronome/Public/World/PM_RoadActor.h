// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PM_PoolableActorInterface.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "PM_RoadActor.generated.h"

UCLASS()
class PROJECTMETRONOME_API APM_RoadActor : public AStaticMeshActor, public IPM_PoolableActorInterface
{
	GENERATED_BODY()
	
public:	
	APM_RoadActor();

	void AddOwnedActor(AActor* OwnedActor);
	void RemoveOwnedActor(AActor* OwnedActor);
	void ReturnAllOwnedActors();

	FORCEINLINE float GetDistance() const { return GetActorLocation().X; }
	
protected:
	virtual void BeginPlay() override;
	
	virtual void SetActive(const bool bActiveState) override;
	virtual bool IsActive() const override { return bIsActive; }

	virtual void OnActorPoolRequested() override { }
	virtual void OnActorPoolReturned() override { } 

private:
	TArray<TWeakObjectPtr<AActor>> OwnedActors;
	bool bIsActive = false;
};
