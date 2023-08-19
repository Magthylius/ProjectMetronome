// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PM_RoadBarrelObstacle.h"

#include "ProjectMetronome.h"
#include "Shell/PM_LogUtil.h"

APM_RoadBarrelObstacle::APM_RoadBarrelObstacle()
{
	BodyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("BodyStaticMesh");
	BodyStaticMesh->SetEnableGravity(false);
	BodyStaticMesh->SetMobility(EComponentMobility::Movable);
	BodyStaticMesh->SetSimulatePhysics(true);
	BodyStaticMesh->SetNotifyRigidBodyCollision(true);
	RootComponent = BodyStaticMesh;
}

void APM_RoadBarrelObstacle::SetActive(const bool bActiveState)
{
	Super::SetActive(bActiveState);
	if (!bActiveState)
	{
		BodyStaticMesh->SetEnableGravity(false);
	}

	BodyStaticMesh->SetSimulatePhysics(bActiveState);
}

void APM_RoadBarrelObstacle::OnMainPawnHit(APM_MainPawn* MainPawn)
{
	Super::OnMainPawnHit(MainPawn);
	
	BodyStaticMesh->SetEnableGravity(true);

	FVector CrashVector = BodyStaticMesh->GetPhysicsLinearVelocity();
	CrashVector += BodyStaticMesh->GetUpVector() * CrashForce;
	BodyStaticMesh->SetPhysicsLinearVelocity(CrashVector);
}
