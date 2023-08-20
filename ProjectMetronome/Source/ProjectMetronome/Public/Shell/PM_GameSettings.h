// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PM_GameSettings.generated.h"


USTRUCT(BlueprintType)
struct PROJECTMETRONOME_API FPM_GameSettings
{
	GENERATED_BODY()

public:
	inline static float PlayerLateralSpeed = 2000.f;
	inline static float PlayerLateralAcceleration = 4000.f;
	inline static float PlayerForwardSpeedCap = 20.f;
	inline static float PlayerForwardAcceleration = 5.f;
	inline static float ObstacleScore = 20.f;
	inline static float ObstaclePenalty = 50.f;
	inline static float ObstacleReturnTime = 1.f;
	
	void ApplyStatics() const;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float DefaultPlayerLateralSpeed = 2000.f;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float DefaultPlayerLateralAcceleration = 4000.f;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float DefaultPlayerForwardSpeedCap = 20.f;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float DefaultObstacleScore = 20.f;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float DefaultObstaclePenalty = 50.f;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float DefaultObstacleReturnTime = 1.f;
};
