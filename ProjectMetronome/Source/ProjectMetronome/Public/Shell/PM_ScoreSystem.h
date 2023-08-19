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
	FORCEINLINE static void NotifyObstacleHit() { ObstaclesHit++; }
	
	FORCEINLINE static float CalculateScore() { return (TotalDistance * 0.05f) - (ObstaclesHit * FPM_GameSettings::ObstaclePenalty); }

	FORCEINLINE static float GetTotalDistance() { return TotalDistance; }
	
	FORCEINLINE static void ResetStats()
	{
		TotalDistance = 0;
		ObstaclesHit = 0;
	}

private:
	inline static float TotalDistance = 0;
	inline static int ObstaclesHit = 0;
};
