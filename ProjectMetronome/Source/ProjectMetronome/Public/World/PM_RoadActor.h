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

	float PerformChancedVeer();

	FORCEINLINE void NotifyRoadSpawned() { OnRoadSpawned(); }
	FORCEINLINE float GetDistance() const { return GetActorLocation().X; }
	FORCEINLINE bool GetHasToVeered() const { return bHasVeered; }
	
protected:
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void SetActive(const bool bActiveState) override;
	virtual bool IsActive() const override { return bIsActive; }

	virtual void OnActorPoolRequested() override { }
	virtual void OnActorPoolReturned() override { }

	virtual void OnRoadSpawned();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess, ClampMin = 0.f, ClampMax = 1.0f))
	float VeerChance = 0.3f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess))
	FVector2D VeerRange = FVector2D(500.0f, 1000.f);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess, ClampMin = 0.f))
	float VeerSpeed = 5.f;
	
	TArray<TWeakObjectPtr<AActor>> OwnedActors;
	bool bIsActive = false;

	bool bHasVeered = false;
	bool bWantsToVeer = false;
	FVector OriginalPosition;
	FVector TargetPosition;
};
