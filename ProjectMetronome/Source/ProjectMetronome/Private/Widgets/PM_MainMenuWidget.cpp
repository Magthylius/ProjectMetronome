// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PM_MainMenuWidget.h"

#include "Shell/PM_GameSettings.h"

void UPM_MainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	const FString MaxSpeed = "Max Speed: " + FString::SanitizeFloat(FPM_GameSettings::PlayerForwardSpeedCap);
	const FString Acceleration = "Acceleration: " + FString::SanitizeFloat(FPM_GameSettings::PlayerForwardAcceleration);
	const FString ObstacleScore = "Obstacle Score: " + FString::SanitizeFloat(FPM_GameSettings::ObstacleScore);
	const FString ObstaclePenalty = "Obstacle Penalty: " + FString::SanitizeFloat(FPM_GameSettings::ObstaclePenalty);
	
	StartGameButton->OnClicked.AddUniqueDynamic(this, &UPM_MainMenuWidget::OnStartGameButton);
	PlayerMaxSpeedText->SetText(FText::FromString(MaxSpeed));
	PlayerAccelerationText->SetText(FText::FromString(Acceleration));
	ObstacleScoreText->SetText(FText::FromString(ObstacleScore));
	ObstaclePenaltyText->SetText(FText::FromString(ObstaclePenalty));
}

void UPM_MainMenuWidget::OnStartGameButton()
{
	OnGameStart.Broadcast();
}
