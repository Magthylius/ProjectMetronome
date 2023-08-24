// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shell/PM_GameSettings.h"
#include "PM_ScoreSystem.generated.h"


USTRUCT(BlueprintType)
struct PROJECTMETRONOME_API FPM_ScoreSystem
{
	GENERATED_BODY()

public:
	FORCEINLINE static void SetTotalDistance(const float NewTotalDistance) { TotalDistance = NewTotalDistance; }
	FORCEINLINE static void SetCurrentSpeed(const float NewSpeed) { CurrentSpeed = NewSpeed; }
	FORCEINLINE static void NotifyObstacleHit() { ObstaclesHit++; }
	FORCEINLINE static void NotifyObstaclePassed() { ObstaclesPassed++; }
	FORCEINLINE static void NotifyFellOff() { TimesFellOff++; }

	FORCEINLINE static float GetTotalDistance() { return TotalDistance; }
	FORCEINLINE static int GetObstaclesHit() { return ObstaclesHit; }
	FORCEINLINE static int GetObstaclesPassed() { return ObstaclesPassed; }
	FORCEINLINE static int GetTimesFellOff() { return TimesFellOff; }
	FORCEINLINE static int GetCurrentSpeed() { return CurrentSpeed; }
	
	FORCEINLINE static float CalculateScore()
	{
		return (ObstaclesPassed * FPM_GameSettings::ObstacleScore) -
				(ObstaclesHit * FPM_GameSettings::ObstaclePenalty) -
				(TimesFellOff * FPM_GameSettings::FellOffPenalty);
	}

	FORCEINLINE static void ResetStats()
	{
		TotalDistance = 0;
		ObstaclesHit = 0;
		ObstaclesPassed = 0;
		TimesFellOff = 0;
		CurrentSpeed = 0;
	}

private:
	inline static float TotalDistance = 0;
	inline static int ObstaclesHit = 0;
	inline static int ObstaclesPassed = 0;
	inline static int TimesFellOff = 0;
	inline static float CurrentSpeed = 0;
};
