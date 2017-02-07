#pragma once

#include "GOAPerSettings.generated.h"


/**
 * Implements the settings for the GOAPer Plugin
 */
UCLASS(config=GOAPer, BlueprintType)
class UGOAPerSettings
	: public UObject
{
	GENERATED_BODY()

public:

	/** A test bool */
	UPROPERTY(config, EditAnywhere, Category="GOAPer")
	bool Test;

	/** A test state*/
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category=RemoteServer)
	TArray<FString> AState;

	/** The IP endpoint to listen to when the Remote Server runs in a game. */
	UPROPERTY(config, EditAnywhere, Category=RemoteServer)
	FString A;

	UFUNCTION(BlueprintPure, Category = GOAPer)
	TArray<FString> GetStateSettings();
};
