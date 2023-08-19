// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PM_MainPawn.h"

/* --- PUBLIC --- */

APM_MainPawn::APM_MainPawn()
{
	BodyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("BodyRoot");
	RootComponent = BodyStaticMesh;
	
	PrimaryActorTick.bCanEverTick = true;
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


