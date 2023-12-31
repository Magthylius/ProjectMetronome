// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/PM_DriveMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "PM_MainPawn.generated.h"

/* Player's main pawn. */
UCLASS()
class PROJECTMETRONOME_API APM_MainPawn : public APawn
{
	GENERATED_BODY()

public:
	APM_MainPawn();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual UPawnMovementComponent* GetMovementComponent() const override { return DriveMovementComponent; }
	
	void TakeSlowDamage(const float SlowDamage);
	void ResetSpeed() { CurrentSpeed = 0.f; }

	FORCEINLINE void SetAllowMovement(const bool bAllow) { bAllowMovement = bAllow; }
	FORCEINLINE float GetDistance() const { return GetActorLocation().X; }

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

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	bool bAllowMovement = false;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	float CurrentSpeedCap = 0.f;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	float CurrentSpeed = 0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input References", meta = (AllowPrivateAccess))
	TObjectPtr<UInputMappingContext> PlayerMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input References", meta = (AllowPrivateAccess))
	TObjectPtr<UInputAction> PlayerMoveAction;
	
	void OnPerformMove(const FInputActionValue& InputValue);
};
