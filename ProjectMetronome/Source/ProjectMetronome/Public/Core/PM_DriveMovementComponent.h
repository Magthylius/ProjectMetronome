// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PM_DriveMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTMETRONOME_API UPM_DriveMovementComponent : public UFloatingPawnMovement
{
	GENERATED_BODY()

public:
	UPM_DriveMovementComponent();
	
	virtual void AddInputVector(FVector WorldVector, bool bForce) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
