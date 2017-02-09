#pragma once

#include "SlateBasics.h"

class SGOAPAtomWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGOAPAtomWidget)
	: _ParentStateWidget() {}
	SLATE_ARGUMENT(TWeakPtr<class SGOAPStateWidget>, ParentStateWidget);
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);

	/* The list of States */
	TSharedPtr<FString> SelectedState;
	bool isChecked;

	// The actual data structure we want to pass back.
	TSharedPtr<FGOAPAtom> Atom;

	TWeakPtr<class SGOAPStateWidget> ParentStateWidget;

	TArray<TSharedPtr<FString>> StateOptions;

	void OnGOAPStateChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo);
	void OnGOAPCheckStateChanged(ECheckBoxState NewState);
};