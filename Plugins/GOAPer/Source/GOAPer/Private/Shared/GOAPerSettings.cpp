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
