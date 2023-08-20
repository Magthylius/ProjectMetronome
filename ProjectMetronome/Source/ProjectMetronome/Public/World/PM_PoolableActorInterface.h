// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PM_PoolableActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPM_PoolableActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTMETRONOME_API IPM_PoolableActorInterface
{
	GENERATED_BODY()

public:
	virtual void SetActive(const bool bActiveState) = 0;
	virtual bool IsActive() const = 0;

	virtual void OnActorPoolRequested() = 0;
	virtual void OnActorPoolReturned() = 0;
};
