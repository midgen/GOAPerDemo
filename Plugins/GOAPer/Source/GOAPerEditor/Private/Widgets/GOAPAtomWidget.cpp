#include "GOAPerEditor.h"
#include "Shared/GOAPerSettings.h"
#include "GOAPAtomWidget.h"
#include "STextComboBox.h"
#include "SCheckBox.h"

#define LOCTEXT_NAMESPACE "GOAPStateCustomization"

void SGOAPAtomWidget::Construct(const FArguments& Args)
{
	UGOAPerSettings* Settings = GetMutableDefault<UGOAPerSettings>();
	if (Settings)
	{
		for (FString& state : Settings->AState)
		{
			StateOptions.Add(MakeShareable<FString>(&state));
		}
	}


	ChildSlot
		[
			//Creating the button that adds a new item on the list when pressed
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot() .HAlign(HAlign_Left)
			[
				SNew(STextComboBox)
				.OptionsSource(&StateOptions)
				.InitiallySelectedItem(StateOptions[0])
				.OnSelectionChanged(this, &SGOAPAtomWidget::OnGOAPStateChanged)
				.ToolTipText(LOCTEXT("Extra info", "My tooltip text"))

			]   
			+ SHorizontalBox::Slot() .HAlign(HAlign_Right)
			[
				SNew(SCheckBox)
				.IsFocusable(true)
				.OnCheckStateChanged(this, &SGOAPAtomWidget::OnGOAPCheckStateChanged)
			]

		];
}




void SGOAPAtomWidget::OnGOAPCheckStateChanged(ECheckBoxState NewState)
{
	isChecked = NewState == ECheckBoxState::Checked;
}

void SGOAPAtomWidget::OnGOAPStateChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo)
{
	SelectedState = ItemSelected;
}

#undef LOCTEXT_NAMESPACE