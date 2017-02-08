#pragma once

#include "SlateBasics.h"

class SGOAPAtomWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGOAPAtomWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);

	/* The list of States */
	TSharedPtr<FString> SelectedState;
	bool isChecked;

	TArray<TSharedPtr<FString>> StateOptions;

	void OnGOAPStateChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo);
	void OnGOAPCheckStateChanged(ECheckBoxState NewState);
};