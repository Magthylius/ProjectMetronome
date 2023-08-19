// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PM_MainHUD.h"

void APM_MainHUD::BeginPlay()
{
	Super::BeginPlay();
	GameHUDWidget = CreateWidget<UPM_GameHUDWidget>(GetOwningPlayerController(), GameHUDWidgetClass);
	GameHUDWidget->AddToViewport();
}
