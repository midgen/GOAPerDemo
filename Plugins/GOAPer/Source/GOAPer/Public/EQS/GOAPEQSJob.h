#pragma once
#include "GOAPer.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "GOAPEQSJob.generated.h"

USTRUCT(BlueprintType)
struct GOAPER_API FGOAPEQSJob
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
	TWeakObjectPtr<UGOAPAction> CallingAction;

	UPROPERTY()
	UEnvQuery* Query;

	UPROPERTY()
	TEnumAsByte<EEnvQueryRunMode::Type> RunMode;


};