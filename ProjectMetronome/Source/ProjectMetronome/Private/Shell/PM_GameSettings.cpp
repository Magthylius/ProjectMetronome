// Fill out your copyright notice in the Description page of Project Settings.


#include "Shell/PM_GameSettings.h"

void FPM_GameSettings::ApplyStatics() const
{
	PlayerLateralSpeed = DefaultPlayerLateralSpeed;
	PlayerLateralAcceleration = DefaultPlayerLateralAcceleration;
	PlayerForwardSpeedCap = DefaultPlayerForwardSpeedCap;
	
	ObstacleScore = DefaultObstacleScore;
	ObstaclePenalty = DefaultObstaclePenalty;
	ObstacleReturnTime = DefaultObstacleReturnTime;

	CameraDistance = DefaultCameraDistance;
	CameraOffset = DefaultCameraOffset;
}
