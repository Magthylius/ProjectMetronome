// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PM_MainGameMode.h"

#include "Core/PM_MainGameState.h"
#include "Core/PM_MainPawn.h"
#include "Core/PM_MainPlayerController.h"

APM_MainGameMode::APM_MainGameMode()
{
	GameStateClass = APM_MainGameState::StaticClass();
	DefaultPawnClass = APM_MainPawn::StaticClass();
	PlayerControllerClass = APM_MainPlayerController::StaticClass();
}
