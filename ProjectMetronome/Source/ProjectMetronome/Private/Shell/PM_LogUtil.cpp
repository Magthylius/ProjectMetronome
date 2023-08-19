#include "Shell/PM_LogUtil.h"

void FPM_LogUtil::PrintScreen(const FString& Message, const float DisplayTime, const FColor Color)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(0, DisplayTime, Color, Message);
}

FString FPM_LogUtil::FromBool(const bool bBoolean)
{
	return bBoolean ? "True" : "False";
}
