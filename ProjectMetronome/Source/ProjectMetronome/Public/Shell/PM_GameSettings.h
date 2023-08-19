// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PM_GameSettings.generated.h"


USTRUCT(BlueprintType)
struct PROJECTMETRONOME_API FPM_GameSettings
{
	GENERATED_BODY()

public:
	inline static float PlayerSpeed = 2000.f;
	inline static float PlayerAcceleration = 4000.f;
	inline static float ForwardSpeed = 20.f;
	inline static float ObstaclePenalty = 50.f;
	
	void ApplyStatics() const;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float DefaultPlayerSpeed = 2000.f;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float DefaultPlayerAcceleration = 4000.f;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float DefaultForwardSpeed = 20.f;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float DefaultObstaclePenalty = 20.f;
};
