#include "GOAPerEditor.h"
#include "Shared/GOAPerSettings.h"
#include "GOAPStateWidget.h"

#define LOCTEXT_NAMESPACE "GOAPStateCustomization"

void SGOAPStateWidget::Construct(const FArguments& Args)
{
	UGOAPerSettings* Settings = GetMutableDefault<UGOAPerSettings>();
	if (Settings)
	{
		for (FString& state : Settings->AState)
		{
			Items.Add(MakeShareable<FString>(&state));
		}
	}


	ChildSlot
		[
			//Creating the button that adds a new item on the list when pressed
			SNew(SScrollBox)
			+ SScrollBox::Slot()
		[
			SNew(SButton)
			.Text(LOCTEXT("Extra info", "Add State"))
		.OnClicked(this, &SGOAPStateWidget::ButtonPressed)
		]

	//The actual list view creation
	+ SScrollBox::Slot()
		[
			SAssignNew(ListViewWidget, SListView<TSharedPtr<FString>>)
			.ItemHeight(24)
		.ListItemsSource(&Items) //The Items array is the source of this listview
		.OnGenerateRow(this, &SGOAPStateWidget::OnGenerateRowForList)
		]
		];
}

FReply SGOAPStateWidget::ButtonPressed()
{
	//Adds a new item to the array (do whatever you want with this)
	Items.Add(MakeShareable(new FString("Hello 1")));

	//Update the listview
	ListViewWidget->RequestListRefresh();

	return FReply::Handled();
}


TSharedRef<ITableRow> SGOAPStateWidget::OnGenerateRowForList(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	//Create the row
	return
		SNew(STableRow< TSharedPtr<FString> >, OwnerTable)
		.Padding(2.0f)
		[
			SNew(STextBlock).Text(FText::FromString(*Item))
		];
}

#undef LOCTEXT_NAMESPACE