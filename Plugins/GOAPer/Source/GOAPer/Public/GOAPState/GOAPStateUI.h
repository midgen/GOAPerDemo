#pragma once
#pragma once

#include "GOAPStateUI.generated.h"

USTRUCT()
struct GOAPER_API FGOAPStateUI
{
	GENERATED_USTRUCT_BODY()
public:

	FGOAPStateUI() {};
	~FGOAPStateUI() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGOAPAtom> State;

};