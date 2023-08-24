// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/PM_MainPawn.h"
#include "World/PM_ActorPoolerSubsystem.h"
#include "World/PM_PoolableActorInterface.h"
#include "World/PM_RoadActor.h"
#include "PM_RoadObstacleActor.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FPM_MainPawnCollisionEvent, class APM_RoadObstacleActor* ObstacleActor);

/* Base abstract class for any road obstacle actor. */
UCLASS(Abstract)
class PROJECTMETRONOME_API APM_RoadObstacleActor : public AActor, public IPM_PoolableActorInterface
{
	GENERATED_BODY()

	friend class APM_RoadActor;

public:
	FPM_MainPawnCollisionEvent OnMainPawnCollided;

	APM_RoadObstacleActor();
	
	virtual void SetActive(const bool bActiveState) override;
	virtual bool IsActive() const override { return bIsActive; }
	
	virtual void SetOwningRoad(APM_RoadActor* RoadActor);
	virtual void StartReturnCountdown(UPM_ActorPoolerSubsystem* PoolerSubsystem, const float Countdown);

	void PerformRandomSpawnEffects();
	
	FORCEINLINE virtual float GetSlowDamage() const { return SlowDamage; }
	FORCEINLINE virtual float GetDistance() const { return GetActorLocation().X; }

	FORCEINLINE void NotifyObstacleSpawned() { OnObstacleSpawned(); }

protected:
	virtual void BeginPlay() override;
	
	virtual void OnActorPoolRequested() override { }
	virtual void OnActorPoolReturned() override { }
	
	virtual void OnMainPawnHit(APM_MainPawn* MainPawn) { }
	virtual void OnObstacleSpawned();

	virtual void OnSpawnRandomSize(const FVector RandomSizeMultiplier) { }
	virtual void OnSpawnRandomColor(const FColor Color) { }

	FORCEINLINE FVector GetOriginalScale() const { return OriginalScale; }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess))
	float SlowDamage = 5.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings | Random Spawn Settings", meta = (AllowPrivateAccess))
	bool bWantsRandomSize;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings | Random Spawn Settings", meta = (AllowPrivateAccess, EditCondition = "bWantsRandomSize", EditConditionHides))
	FVector MinRandomSize = FVector::One();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings | Random Spawn Settings", meta = (AllowPrivateAccess, EditCondition = "bWantsRandomSize", EditConditionHides))
	FVector MaxRandomSize = FVector::One() * 2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings | Random Spawn Settings", meta = (AllowPrivateAccess))
	bool bWantsRandomColor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings | Random Spawn Settings", meta = (AllowPrivateAccess, EditCondition = "bWantsRandomColor", EditConditionHides))
	TArray<FColor> RandomColorRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	TWeakObjectPtr<APM_RoadActor> OwningRoadActor;

	FVector OriginalScale;
	
	FTimerHandle ReturnHandle;
	bool bIsActive;
	bool bHasBeenCollided;

	UFUNCTION(BlueprintCosmetic)
	virtual void OnActorWasHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
