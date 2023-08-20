// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PM_MainPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ProjectMetronome.h"
#include "Core/PM_MainPlayerController.h"
#include "Shell/PM_GameSettings.h"
#include "Shell/PM_ScoreSystem.h"

/* --- PUBLIC --- */

APM_MainPawn::APM_MainPawn()
{
	BodyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("BodyRoot");
	RootComponent = BodyStaticMesh;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 3500.f;
	CameraBoom->SocketOffset = FVector(0, 0, 1000.f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	DriveMovementComponent = CreateDefaultSubobject<UPM_DriveMovementComponent>("DriveMovementComponent");
	DriveMovementComponent->SetUpdatedComponent(BodyStaticMesh);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void APM_MainPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(PlayerMoveAction, ETriggerEvent::Triggered, this, &APM_MainPawn::OnPerformMove);
	}
}

void APM_MainPawn::TakeSlowDamage(const float SlowDamage)
{
	CurrentSpeed = FMath::Max(CurrentSpeed - SlowDamage, 0.f);
}

/* --- PROTECTED --- */

void APM_MainPawn::BeginPlay()
{
	Super::BeginPlay();

	const APM_MainPlayerController* MainPlayerController = GetController<APM_MainPlayerController>();
	if (!ensure(IsValid(MainPlayerController)))
	{
		UE_LOG(LogPMCore, Error, TEXT("APM_MainPawn: Invalid main player controller."));
		return;
	}
	
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(MainPlayerController->GetLocalPlayer());
	if (!ensure(IsValid(InputSubsystem)))
	{
		UE_LOG(LogPMCore, Error, TEXT("APM_MainPawn: Invalid input subsystem."));
		return;
	}

	InputSubsystem->AddMappingContext(PlayerMappingContext, 0);
	DriveMovementComponent->MaxSpeed = FPM_GameSettings::PlayerLateralSpeed;
	DriveMovementComponent->Acceleration = FPM_GameSettings::PlayerLateralAcceleration;
	CurrentSpeedCap = FPM_GameSettings::PlayerForwardSpeedCap;
}

void APM_MainPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentSpeed = FMath::Min(CurrentSpeed + FPM_GameSettings::PlayerForwardAcceleration * DeltaTime, CurrentSpeedCap);
	
	AddActorLocalOffset(FVector::ForwardVector * CurrentSpeed);
	FPM_ScoreSystem::SetTotalDistance(GetDistance());
}

/* --- PRIVATE --- */

void APM_MainPawn::OnPerformMove(const FInputActionValue& InputValue)
{
	const float MoveInput = InputValue.Get<float>();
	AddMovementInput(FVector::LeftVector * MoveInput);
}
