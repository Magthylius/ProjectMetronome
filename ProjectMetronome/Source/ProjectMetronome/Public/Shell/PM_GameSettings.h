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
	inline static float FellOffPenalty = 1000.0;

	inline static float CameraDistance = 5000.f;
	inline static float CameraOffset = 1500.f;
	
	void ApplyStatics() const;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float DefaultPlayerLateralSpeed = PlayerLateralSpeed;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float DefaultPlayerLateralAcceleration = PlayerLateralAcceleration;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float DefaultPlayerForwardSpeedCap = PlayerForwardSpeedCap;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float DefaultPlayerForwardAcceleration = PlayerForwardAcceleration;
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float DefaultObstacleScore = ObstacleScore;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float DefaultObstaclePenalty = ObstaclePenalty;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float DefaultObstacleReturnTime = ObstacleReturnTime;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float DefaultFellOffPenalty = FellOffPenalty;
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float DefaultCameraDistance = CameraDistance;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float DefaultCameraOffset = CameraOffset;
};
