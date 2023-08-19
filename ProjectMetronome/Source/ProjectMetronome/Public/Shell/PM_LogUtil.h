#pragma once

#include "CoreMinimal.h"

class FPM_LogUtil
{
public:
	static void PrintScreen(const FString& Message, const float DisplayTime = 10.f, const FColor Color = FColor::Cyan);
	static FString FromBool(const bool bBoolean);
};
