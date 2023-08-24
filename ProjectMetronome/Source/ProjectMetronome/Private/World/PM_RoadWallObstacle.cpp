// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PM_RoadWallObstacle.h"

/* --- PUBLIC --- */

APM_RoadWallObstacle::APM_RoadWallObstacle()
{
	BodyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("BodyStaticMesh");
	BodyStaticMesh->SetEnableGravity(true);
	BodyStaticMesh->SetMobility(EComponentMobility::Movable);
	BodyStaticMesh->SetSimulatePhysics(true);
	BodyStaticMesh->SetNotifyRigidBodyCollision(true);
	RootComponent = BodyStaticMesh;

	PrimaryActorTick.bCanEverTick = true;
}

void APM_RoadWallObstacle::SetActive(const bool bActiveState)
{
	Super::SetActive(bActiveState);

	BodyStaticMesh->SetEnableGravity(bActiveState);
	BodyStaticMesh->SetSimulatePhysics(bActiveState);
	BodyStaticMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
	BodyStaticMesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);

	SetActorRotation(FRotator::ZeroRotator);
	ChangeMovementMode(EPM_WallMovementMode::Idle);
	GetWorld()->GetTimerManager().ClearTimer(ChangeMovementHandle);
}

/* --- PROTECTED --- */

void APM_RoadWallObstacle::BeginPlay()
{
	Super::BeginPlay();
	InterpolationSpeed = GetWorld()->GetDeltaSeconds() / InterpolationTime;
}

void APM_RoadWallObstacle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (MovementMode == EPM_WallMovementMode::Idle) return;
	const FVector NewLocation = FMath::Lerp(GetActorLocation(), TargetPosition, DeltaSeconds / InterpolationTime);
	SetActorLocation(NewLocation);
	UE_LOG(LogPMWorld, VeryVerbose, TEXT("APM_RoadWallObstacle [%s]: Is moving to %s."), *GetName(), *NewLocation.ToString());
}

void APM_RoadWallObstacle::OnMainPawnHit(APM_MainPawn* MainPawn)
{
	Super::OnMainPawnHit(MainPawn);
	BodyStaticMesh->SetEnableGravity(true);
	ChangeMovementMode(EPM_WallMovementMode::Idle);
}

void APM_RoadWallObstacle::OnObstacleSpawned()
{
	Super::OnObstacleSpawned();
	BodyStaticMesh->SetAllPhysicsLinearVelocity(FVector::ZeroVector);
	BodyStaticMesh->SetAllPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	OriginalPosition = GetActorLocation();
	ChangeMovementMode(FMath::RandBool() ? EPM_WallMovementMode::MovingLeft : EPM_WallMovementMode::MovingRight);

	GetWorld()->GetTimerManager().SetTimer(ChangeMovementHandle, this, &APM_RoadWallObstacle::ToggleMovementMode, InterpolationTime, true);
}

void APM_RoadWallObstacle::OnSpawnRandomSize(const FVector RandomSizeMultiplier)
{
	Super::OnSpawnRandomSize(RandomSizeMultiplier);
	SetActorScale3D(GetOriginalScale() * RandomSizeMultiplier);
}

void APM_RoadWallObstacle::OnSpawnRandomColor(const FColor Color)
{
	Super::OnSpawnRandomColor(Color);
	UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(BodyStaticMesh->GetMaterial(0));
	if (IsValid(Material))
	{
		Material->SetVectorParameterValue("Color", Color);
	}
}

/* --- PRIVATE --- */

void APM_RoadWallObstacle::ToggleMovementMode()
{
	switch (MovementMode)
	{
	case EPM_WallMovementMode::MovingLeft:
		ChangeMovementMode(EPM_WallMovementMode::MovingRight);
		break;

	case EPM_WallMovementMode::MovingRight:
		ChangeMovementMode(EPM_WallMovementMode::MovingLeft);
		break;

	case EPM_WallMovementMode::Idle:
	default: break;
	}
}

void APM_RoadWallObstacle::ChangeMovementMode(const EPM_WallMovementMode NewMovementMode)
{
	MovementMode = NewMovementMode;
	switch (MovementMode)
	{
	case EPM_WallMovementMode::MovingLeft:
		TargetPosition = OriginalPosition - (GetActorRightVector() * SideMovementRange);
		break;

	case EPM_WallMovementMode::MovingRight:
		TargetPosition = OriginalPosition + (GetActorRightVector() * SideMovementRange);
		break;

	case EPM_WallMovementMode::Idle:
	default: break;
	}
}
