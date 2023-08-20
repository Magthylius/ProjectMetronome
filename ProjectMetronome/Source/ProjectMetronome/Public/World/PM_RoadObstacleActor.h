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

	FORCEINLINE virtual float GetSlowDamage() const { return SlowDamage; }

	virtual float GetDistance() const { return GetActorLocation().X; }
	virtual void SetOwningRoad(APM_RoadActor* RoadActor) { OwningRoadActor = RoadActor; }
	virtual void StartReturnCountdown(UPM_ActorPoolerSubsystem* PoolerSubsystem, const float Countdown);

protected:
	virtual void OnMainPawnHit(APM_MainPawn* MainPawn) { }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess))
	float SlowDamage = 5.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	TWeakObjectPtr<APM_RoadActor> OwningRoadActor;

	FTimerHandle ReturnHandle;
	bool bIsActive;
	bool bHasBeenCollided;

	UFUNCTION(BlueprintCosmetic)
	virtual void OnActorWasHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
