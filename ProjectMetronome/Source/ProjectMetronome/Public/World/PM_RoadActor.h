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

protected:
	virtual void BeginPlay() override;
	
	virtual void SetActive(const bool bActiveState) override;
	virtual bool IsActive() const override { return bIsActive; }

private:
	bool bIsActive = false;
};
