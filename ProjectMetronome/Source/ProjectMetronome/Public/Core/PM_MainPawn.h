// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PM_DriveMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "PM_MainPawn.generated.h"

UCLASS()
class PROJECTMETRONOME_API APM_MainPawn : public APawn
{
	GENERATED_BODY()

public:
	APM_MainPawn();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual UPawnMovementComponent* GetMovementComponent() const override { return DriveMovementComponent; }

	FORCEINLINE UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> BodyStaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UPM_DriveMovementComponent> DriveMovementComponent;
};
