#include "GOAPerEditor.h"
#include "Shared/GOAPerSettings.h"
#include "GOAPStateWidget.h"
#include "GOAPAtomWidget.h"
#include "SListView.h"

#define LOCTEXT_NAMESPACE "GOAPStateCustomization"

void SGOAPStateWidget::Construct(const FArguments& Args)
{

	ChildSlot
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
		[
			SNew(SButton)
			.Text(FText::FromString(TEXT("Add new list item")))
		.OnClicked(this, &SGOAPStateWidget::ButtonPressed)
		]

	//The actual list view creation
	+ SScrollBox::Slot()
		[
			SAssignNew(AtomsWidget, SListView<TSharedPtr<FGOAPAtom>>)
			.ItemHeight(24)
		.ListItemsSource(&Atoms) //The Items array is the source of this listview
		.OnGenerateRow(this, &SGOAPStateWidget::OnGenerateRowForList)
		]
		];
}



FReply SGOAPStateWidget::ButtonPressed()
{
	//Adds a new item to the array (do whatever you want with this)
	Atoms.Add(MakeShareable(new FGOAPAtom(0, false)));

	//Update the listview
	AtomsWidget->RequestListRefresh();

	return FReply::Handled();
}

TSharedRef<ITableRow> SGOAPStateWidget::OnGenerateRowForList(TSharedPtr<FGOAPAtom> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	//Create the row
	return
		SNew(STableRow< TSharedPtr<FGOAPAtom> >, OwnerTable)
		.Padding(2.0f)
		[
			SNew(SGOAPAtomWidget)
		];
}

#undef LOCTEXT_NAMESPACE