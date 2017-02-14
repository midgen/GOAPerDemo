#include "GOAPer.h"
#include "GOAPerBPFunctionLibary.h"

void UGOAPerBlueprintFunctionLibrary::SetGOAPState(UObject* WorldContextObject, AGOAPAIController* Controller, const uint8 State, const bool Value)
{
	if (Controller)
	{
		Controller->SetGOAPStateSafe(State, Value);
	}
}