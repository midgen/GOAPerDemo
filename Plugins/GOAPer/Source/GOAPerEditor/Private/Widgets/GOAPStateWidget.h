#pragma once
#include "GOAPAtom.h"
#include "SlateBasics.h"

class SGOAPStateWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGOAPStateWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);

	FReply ButtonPressed();

	TArray<TSharedPtr<FGOAPAtom>> Atoms;

	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FGOAPAtom> Item, const TSharedRef<STableViewBase>& OwnerTable);

	TSharedPtr<SListView<TSharedPtr<FGOAPAtom>>> AtomsWidget;
	
};