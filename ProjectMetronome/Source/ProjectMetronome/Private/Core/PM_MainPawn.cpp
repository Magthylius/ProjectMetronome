// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PM_MainPawn.h"

// Sets default values
APM_MainPawn::APM_MainPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APM_MainPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APM_MainPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APM_MainPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

