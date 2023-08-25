// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PM_GameHUDWidget.h"

#include "Shell/PM_ScoreSystem.h"

void UPM_GameHUDWidget::SetScoring(const float Scoring) const
{
	const FString DisplayScoring = FString::FromInt(FMath::RoundToInt(Scoring));
	ScoringTextBlock->SetText(FText::FromString(DisplayScoring));
}

void UPM_GameHUDWidget::SetDistance(const float Distance) const
{
	const FString DisplayDistance = FString::FromInt(FMath::RoundToInt(Distance));
	DistanceTextBlock->SetText(FText::FromString(DisplayDistance));
}

void UPM_GameHUDWidget::SetSpeed(const float Speed) const
{
	const FString DisplaySpeed = FString::FromInt(FMath::RoundToInt(Speed));
	SpeedTextBlock->SetText(FText::FromString(DisplaySpeed));
}

void UPM_GameHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	SetScoring(FPM_ScoreSystem::CalculateScore());
	SetDistance(FPM_ScoreSystem::GetTotalDistance());
	SetSpeed(FPM_ScoreSystem::GetCurrentSpeed());
}
