// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "World/PM_RoadSubsystem.h"
#include "PM_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMETRONOME_API UPM_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FORCEINLINE FPM_RoadSubsystemInitData GetRoadSubsystemInitData() const { return RoadSubsystemInitData; }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Road Settings", meta = (AllowPrivateAccess))
	FPM_RoadSubsystemInitData RoadSubsystemInitData;
};
