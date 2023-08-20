// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World/PM_RoadObstacleActor.h"
#include "PM_RoadWallObstacle.generated.h"

UENUM()
enum class EPM_WallMovementMode : uint8
{
	Idle,
	MovingLeft,
	MovingRight
};

/**
 * 
 */
UCLASS()
class PROJECTMETRONOME_API APM_RoadWallObstacle : public APM_RoadObstacleActor
{
	GENERATED_BODY()

public:
	APM_RoadWallObstacle();

	virtual void SetActive(const bool bActiveState) override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnMainPawnHit(APM_MainPawn* MainPawn) override;
	virtual void OnObstacleSpawned() override;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> BodyStaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess))
	float SideMovementRange = 500.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess))
	float InterpolationTime = 2.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	EPM_WallMovementMode MovementMode = EPM_WallMovementMode::MovingLeft;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	FVector OriginalPosition = FVector::ZeroVector;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	FVector TargetPosition = OriginalPosition;

	FTimerHandle ChangeMovementHandle;
	float InterpolationSpeed = 1.f;

	void ToggleMovementMode();
	void ChangeMovementMode(const EPM_WallMovementMode NewMovementMode);
};
