// Fill out your copyright notice in the Description page of Project Settings.


#include "Shell/PM_GameSettings.h"

void FPM_GameSettings::ApplyStatics() const
{
	PlayerSpeed = DefaultPlayerSpeed;
	PlayerAcceleration = DefaultPlayerAcceleration;
	ForwardSpeed = DefaultForwardSpeed;
}
