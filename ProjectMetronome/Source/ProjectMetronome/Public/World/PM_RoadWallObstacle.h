// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World/PM_RoadObstacleActor.h"
#include "PM_RoadWallObstacle.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMETRONOME_API APM_RoadWallObstacle : public APM_RoadObstacleActor
{
	GENERATED_BODY()
	
public:
	APM_RoadWallObstacle();
	
	virtual void SetActive(const bool bActiveState) override;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> BodyStaticMesh;
};
