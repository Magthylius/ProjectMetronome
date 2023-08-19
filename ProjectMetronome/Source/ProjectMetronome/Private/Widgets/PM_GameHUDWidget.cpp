// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PM_GameHUDWidget.h"

void UPM_GameHUDWidget::SetScoring(const float Scoring) const
{
	ScoringTextBlock->SetText(FText::FromString(FString::SanitizeFloat(Scoring)));
}

void UPM_GameHUDWidget::SetDistance(const float Distance) const
{
	const FString DisplayDistance = FString::FromInt(FMath::RoundToInt(Distance));
	DistanceTextBlock->SetText(FText::FromString(DisplayDistance));
}
