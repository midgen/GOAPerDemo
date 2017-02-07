#pragma once

#include "GOAPState.generated.h"

USTRUCT()
struct GOAPER_API FGOAPState
{
	GENERATED_USTRUCT_BODY()
public:

	FGOAPState() {};
	~FGOAPState() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<uint8, bool> State;

	FGOAPState& operator+(const FGOAPState& aOther)
	{
		for (auto& elem : aOther.State)
		{
			State.Add(elem.Key, elem.Value);
		}
		return *this;
	}

	bool FGOAPState::IsSatisfiesState(const FGOAPState& aOther)
	{
		for (auto& elem : aOther.State)
		{			
			if (State.Contains(elem.Key))
			{
				bool* val = State.Find(elem.Key);
				if (*val != elem.Value)
				{
					return false;
				}
			}
		}
		return true;
	}

	bool FGOAPState::IsStateSatisfied(const uint8 aState, const bool aValue)
	{
		if (State.Contains(aState))
		{
			bool* val = State.Find(aState);
			if (*val == aValue)
			{
				return true;
			}

		}
		return false;
	}

	void FGOAPState::SetState(const uint8 aState, const bool aValue)
	{
		State.Add(aState, aValue);
	}
};