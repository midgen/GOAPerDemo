#pragma once
#include "GOAPAtom.h"
#include "GOAPState.h"
#include "SlateBasics.h"

class SGOAPStateWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGOAPStateWidget)
		: _GOAPState()
	{}
	SLATE_ARGUMENT(TWeakPtr<FGOAPState>, GOAPState)
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);

	FReply ButtonPressed();

	TWeakPtr<FGOAPState> GOAPState;

	TArray<TSharedPtr<FGOAPAtom>> Atoms;

	TSharedRef<SGOAPStateWidget> thisShared = MakeShareable<SGOAPStateWidget>(this);

	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FGOAPAtom> Item, const TSharedRef<STableViewBase>& OwnerTable);

	TSharedPtr<SListView<TSharedPtr<FGOAPAtom>>> AtomsWidget;
	
};