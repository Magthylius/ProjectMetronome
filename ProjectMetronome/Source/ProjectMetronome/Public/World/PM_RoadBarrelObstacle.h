// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World/PM_RoadObstacleActor.h"
#include "PM_RoadBarrelObstacle.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMETRONOME_API APM_RoadBarrelObstacle : public APM_RoadObstacleActor
{
	GENERATED_BODY()

public:
	APM_RoadBarrelObstacle();

	virtual void SetActive(const bool bActiveState) override;

protected:
	virtual void OnMainPawnHit(APM_MainPawn* MainPawn) override;
	
private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> BodyStaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess))
	float CrashForce = 2000.f;
};
