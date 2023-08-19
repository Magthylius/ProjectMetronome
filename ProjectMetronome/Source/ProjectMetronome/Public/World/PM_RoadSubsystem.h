// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PM_ActorPoolerSubsystem.h"
#include "PM_RoadActor.h"
#include "Core/PM_MainPawn.h"
#include "Subsystems/WorldSubsystem.h"
#include "PM_RoadSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FPM_RoadSubsystemInitData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<APM_RoadActor> RoadClass;
	UPROPERTY(EditAnywhere)
	int RoadTileAmount = 10;
	UPROPERTY(EditAnywhere)
	float RoadTileDistance = 100;

	UPROPERTY(EditAnywhere)
	float RoadBackBuffer = -5000.f;
	UPROPERTY(EditAnywhere)
	int RoadFrontBufferIndex = 3;
};

/**
 * 
 */
UCLASS()
class PROJECTMETRONOME_API UPM_RoadSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual TStatId GetStatId() const override { return TStatId(); } 

	void StartSubsystem(APM_MainPawn* InPlayerPawn, const FPM_RoadSubsystemInitData& InInitData);
	
	FORCEINLINE void SetPlayerPawn(APM_MainPawn* InPlayerPawn) { PlayerPawn = InPlayerPawn; }
	FORCEINLINE void SetAllowObservation(const bool bAllow) { bAllowObservation = bAllow; }

	FORCEINLINE float GetQuantizedPosition(const int OffsetIndex) const;

	
protected:
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<APM_MainPawn> PlayerPawn;
	UPROPERTY(VisibleInstanceOnly)
	TWeakObjectPtr<UPM_ActorPoolerSubsystem> ActorPoolerSubsystem;
	UPROPERTY(VisibleInstanceOnly)
	TArray<TWeakObjectPtr<APM_RoadActor>> RoadActors;
	UPROPERTY(VisibleInstanceOnly)
	FPM_RoadSubsystemInitData InitData;
	
	bool bAllowObservation = false;
	float RoadTileDistance;
};
