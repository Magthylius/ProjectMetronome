// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/PM_GameHUDWidget.h"
#include "GameFramework/HUD.h"
#include "PM_MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMETRONOME_API APM_MainHUD : public AHUD
{
	GENERATED_BODY()

public:
	FORCEINLINE UPM_GameHUDWidget* GetGameHUDWidget() const { return GameHUDWidget; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Referneces", meta = (AllowPrivateAccess))
	TSubclassOf<UPM_GameHUDWidget> GameHUDWidgetClass;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Widget Instances", meta = (AllowPrivateAccess))
	TObjectPtr<UPM_GameHUDWidget> GameHUDWidget;
};
