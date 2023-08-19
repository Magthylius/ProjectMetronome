// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PM_MainGameMode.h"

#include "ProjectMetronome.h"
#include "Core/PM_GameInstance.h"
#include "Core/PM_MainGameState.h"
#include "Core/PM_MainPawn.h"
#include "Core/PM_MainPlayerController.h"

APM_MainGameMode::APM_MainGameMode()
{
	GameStateClass = APM_MainGameState::StaticClass();
	DefaultPawnClass = APM_MainPawn::StaticClass();
	PlayerControllerClass = APM_MainPlayerController::StaticClass();
}

void APM_MainGameMode::BeginPlay()
{
	Super::BeginPlay();

	const UPM_GameInstance* PMGameInstance = GetGameInstance<UPM_GameInstance>();
	if (!ensure(IsValid(PMGameInstance)))
	{
		UE_LOG(LogPMCore, Error, TEXT("APM_MainGameMode: Invalid game instance."));
		return;
	}

	UPM_RoadSubsystem* RoadSubsystem = GetWorld()->GetSubsystem<UPM_RoadSubsystem>();
	RoadSubsystem->StartSubsystem(nullptr, PMGameInstance->GetRoadSubsystemInitData());
}
