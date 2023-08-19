// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PM_RoadActor.h"

APM_RoadActor::APM_RoadActor()
{
}

void APM_RoadActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void APM_RoadActor::SetActive(const bool bActiveState)
{
	bIsActive = bActiveState;
	SetActorHiddenInGame(bActiveState);
	SetActorEnableCollision(bActiveState);
	GetStaticMeshComponent()->SetSimulatePhysics(bActiveState);
}

