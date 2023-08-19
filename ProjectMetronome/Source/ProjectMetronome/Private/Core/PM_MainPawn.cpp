// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PM_MainPawn.h"

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

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; 

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void APM_MainPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/* --- PROTECTED --- */

void APM_MainPawn::BeginPlay()
{
	Super::BeginPlay();
}

void APM_MainPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/* --- PRIVATE --- */


