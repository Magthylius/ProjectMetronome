// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PM_RoadWallObstacle.h"

APM_RoadWallObstacle::APM_RoadWallObstacle()
{
	BodyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("BodyStaticMesh");
	BodyStaticMesh->SetEnableGravity(false);
	BodyStaticMesh->SetMobility(EComponentMobility::Movable);
	BodyStaticMesh->SetSimulatePhysics(true);
	BodyStaticMesh->SetNotifyRigidBodyCollision(true);
	RootComponent = BodyStaticMesh;
}

void APM_RoadWallObstacle::SetActive(const bool bActiveState)
{
	Super::SetActive(bActiveState);

	if (!bActiveState)
	{
		BodyStaticMesh->SetEnableGravity(false);
	}

	BodyStaticMesh->SetSimulatePhysics(bActiveState);
	BodyStaticMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
	BodyStaticMesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	SetActorRotation(FRotator::ZeroRotator);
}
