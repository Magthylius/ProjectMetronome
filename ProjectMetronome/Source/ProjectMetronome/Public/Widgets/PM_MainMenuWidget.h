// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "PM_MainMenuWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FPM_MainMenuEvent);

/* Widget that shows at the start of the game. */
UCLASS()
class PROJECTMETRONOME_API UPM_MainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FPM_MainMenuEvent OnGameStart;
	
protected:
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(VisibleInstanceOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UButton> StartGameButton;
	UPROPERTY(VisibleInstanceOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextBlock> PlayerMaxSpeedText;
	UPROPERTY(VisibleInstanceOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextBlock> PlayerAccelerationText;
	UPROPERTY(VisibleInstanceOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextBlock> ObstacleScoreText;
	UPROPERTY(VisibleInstanceOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextBlock> ObstaclePenaltyText;

	UFUNCTION(BlueprintCosmetic)
	void OnStartGameButton();
};
