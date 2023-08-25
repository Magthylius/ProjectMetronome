// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PM_MainHUD.h"

#include "Core/PM_GameInstance.h"

void APM_MainHUD::BeginPlay()
{
	Super::BeginPlay();
	
	GameHUDWidget = CreateWidget<UPM_GameHUDWidget>(GetOwningPlayerController(), GameHUDWidgetClass);
	MainMenuWidget = CreateWidget<UPM_MainMenuWidget>(GetOwningPlayerController(), MainMenuWidgetClass);
	MainMenuWidget->AddToViewport();
	MainMenuWidget->OnGameStart.AddUObject(this, &APM_MainHUD::OnGameStart);
}

void APM_MainHUD::OnGameStart() const
{
	MainMenuWidget->RemoveFromParent();
	GameHUDWidget->AddToViewport();

	APM_MainPawn* MainPawn = Cast<APM_MainPawn>(GetOwningPawn());
	if (ensure(IsValid(MainPawn))) MainPawn->SetAllowMovement(true);
	
	UPM_RoadSubsystem* RoadSubsystem = GetWorld()->GetSubsystem<UPM_RoadSubsystem>();
	if (ensure(IsValid(RoadSubsystem))) RoadSubsystem->BeginGameplay();

	GetOwningPlayerController()->SetInputMode(FInputModeGameOnly());
}
