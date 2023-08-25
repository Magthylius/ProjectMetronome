// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PM_DriveMovementComponent.h"

UPM_DriveMovementComponent::UPM_DriveMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPM_DriveMovementComponent::AddInputVector(FVector WorldVector, bool bForce)
{
	Super::AddInputVector(WorldVector, bForce);
}

void UPM_DriveMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPM_DriveMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

