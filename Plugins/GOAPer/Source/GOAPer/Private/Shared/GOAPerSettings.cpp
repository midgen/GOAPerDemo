#pragma once
#include "GOAPer.h"
#include "GOAPerSettings.h"


/**
 * Implements the settings for the GOAPer Plugin
 */

TArray<FString> UGOAPerSettings::GetStateSettings()
{
	return AState;
}

FString UGOAPerSettings::GetStringForByte(const uint8 inByte)
{
	FString result = AState[inByte];
	return result;
}

uint8 UGOAPerSettings::GetByteKey(TSharedPtr<FString> inString)
{
	for (uint8 i = 0; i < AState.Num(); ++i)
	{
		if (inString->Compare(AState[i]) == 0)
		{
			return i;
		}
	}

	return 0;
}
