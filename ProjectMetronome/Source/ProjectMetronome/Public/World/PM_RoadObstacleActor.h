// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PM_PoolableActorInterface.h"
#include "Core/PM_MainPawn.h"
#include "PM_RoadObstacleActor.generated.h"

/* Base abstract class for any road obstacle actor. */
UCLASS(Abstract)
class PROJECTMETRONOME_API APM_RoadObstacleActor : public AActor, public IPM_PoolableActorInterface
{
	GENERATED_BODY()

public:
	APM_RoadObstacleActor();
	
	virtual void SetActive(const bool bActiveState) override;
	virtual bool IsActive() const override { return bIsActive; }

	FORCEINLINE virtual float GetSlowDamage() const { return SlowDamage; }

protected:
	virtual void OnMainPawnHit(APM_MainPawn* MainPawn) { }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess))
	float SlowDamage;
	
	bool bIsActive;

	UFUNCTION(BlueprintCosmetic)
	virtual void OnActorWasHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
