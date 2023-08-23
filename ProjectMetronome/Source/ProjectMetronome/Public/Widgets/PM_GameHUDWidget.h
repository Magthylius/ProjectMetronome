// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PM_GameHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMETRONOME_API UPM_GameHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetScoring(const float Scoring) const;
	void SetDistance(const float Distance) const;
	void SetSpeed(const float Speed) const;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextBlock> DistanceTextBlock;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextBlock> ScoringTextBlock;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextBlock> SpeedTextBlock;
};
