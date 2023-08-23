// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Core/PM_MainPawn.h"
#include "World/PM_ActorPoolerSubsystem.h"
#include "World/PM_RoadActor.h"
#include "World/PM_RoadObstacleActor.h"
#include "PM_RoadSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FPM_RoadSubsystemInitData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<APM_RoadActor> RoadClass;
	UPROPERTY(EditAnywhere)
	int RoadTileAmount = 8;
	UPROPERTY(EditAnywhere)
	float RoadTileDistance = 100;
	UPROPERTY(EditAnywhere)
	float RoadVeerDistance = 1000.f;
	UPROPERTY(EditAnywhere)
	float RoadVeeringStartDelay = 5.f;
	UPROPERTY(EditAnywhere)
	int RoadBackBufferIndex = 2;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<APM_RoadObstacleActor>> RoadObstacleTypes;
	UPROPERTY(EditAnywhere)
	int ObstaclePoolAmount = 5;
	UPROPERTY(EditAnywhere)
	float ObstacleStartSpawnDelay = 3.f;
	UPROPERTY(EditAnywhere)
	float ObstacleSpawnInterval = 1.f;
	UPROPERTY(EditAnywhere)
	FVector2D ObstacleSpawnHalfRange = FVector2D(250.f, 1000.f);
	UPROPERTY(EditAnywhere)
	float ObstacleSpawnDistance = 5000.f;
	UPROPERTY(EditAnywhere)
	float ObstacleSpawnHeight = 1000.f;
};

/* Subsystem that handles road tiling and object creation. */
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
	
	/* Road scrolling system. */
	virtual void TickRoadScrolling();
	/* Obstacle spawning system. We don't use a timer so we can set obstacle timing for ramping difficulty. */
	virtual void TickObstacleSpawning();
	/* Obstacle scoring system. Remove from array when passed, add to score. */
	virtual void TickObstacleScoring();
	
private:
	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<APM_MainPawn> PlayerPawn;
	UPROPERTY(VisibleInstanceOnly)
	TWeakObjectPtr<UPM_ActorPoolerSubsystem> ActorPoolerSubsystem;
	UPROPERTY(VisibleInstanceOnly)
	TArray<TWeakObjectPtr<APM_RoadActor>> RoadActors;
	UPROPERTY(VisibleInstanceOnly)
	TArray<TWeakObjectPtr<APM_RoadObstacleActor>> OncomingRoadObstacles;
	UPROPERTY(VisibleInstanceOnly)
	TArray<TWeakObjectPtr<APM_RoadObstacleActor>> UnownedRoadObstacles;
	
	UPROPERTY(VisibleInstanceOnly)
	FPM_RoadSubsystemInitData InitData;

	bool bAllowObservation = false;
	float BackBuffer;

	FTimerHandle RoadVeeringHandle;
	bool bAllowRoadVeering = false;
	int VeerIndex;
	
	FTimerHandle ObstacleSpawnHandle;
	bool bAllowObstacleSpawn = false;
	float NextObstacleSpawnTime = -1.f;

	void SpawnObstacle();

	void OnObstacleCollided(APM_RoadObstacleActor* ObstacleActor) const;
};
