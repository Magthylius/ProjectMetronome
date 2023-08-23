// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PM_RoadBarrelObstacle.h"

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
	BodyStaticMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
	BodyStaticMesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	SetActorRotation(FRotator::ZeroRotator);
}

void APM_RoadBarrelObstacle::OnMainPawnHit(APM_MainPawn* MainPawn)
{
	Super::OnMainPawnHit(MainPawn);
	
	BodyStaticMesh->SetEnableGravity(true);

	FVector CrashVector = BodyStaticMesh->GetPhysicsLinearVelocity();
	CrashVector += BodyStaticMesh->GetUpVector() * CrashForce;
	BodyStaticMesh->SetPhysicsLinearVelocity(CrashVector);
}

void APM_RoadBarrelObstacle::OnSetColor(const FColor Color)
{
	Super::OnSetColor(Color);
	UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(BodyStaticMesh->GetMaterial(0));
	if (IsValid(Material))
	{
		Material->SetVectorParameterValue("Color", Color);
	}
}
