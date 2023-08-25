// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Shell/PM_GameSettings.h"
#include "World/PM_RoadSubsystem.h"
#include "PM_GameInstance.generated.h"

/* Custom game instance class to hold global references and settings. */
UCLASS()
class PROJECTMETRONOME_API UPM_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FORCEINLINE FPM_RoadSubsystemInitData GetRoadSubsystemInitData() const { return RoadSubsystemInitData; }
	FORCEINLINE FPM_GameSettings GetGameSettings() const { return GameSettings; }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	FPM_RoadSubsystemInitData RoadSubsystemInitData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	FPM_GameSettings GameSettings;
};
