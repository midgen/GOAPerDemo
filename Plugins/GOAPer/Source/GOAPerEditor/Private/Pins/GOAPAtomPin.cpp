#include "GOAPerEditor.h"
#include "KismetEditorUtilities.h"
#include "STextComboBox.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "GOAPAtom.h"
#include "GOAPAtomPin.h"

void SGOAPAtomPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{

	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget>	SGOAPAtomPin::GetDefaultValueWidget()
{
	for (auto& stateString : GOAPSettings->AvailableStates)
	{
		AvailableOptions.Add(MakeShareable<FString>(new FString(stateString)));
	}

	//Creating the button that adds a new item on the list when pressed
	SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		[
			SNew(STextComboBox)
			.OptionsSource(&AvailableOptions)
		.OnSelectionChanged(this, &SGOAPAtomPin::OnStateValueChanged)
		.InitiallySelectedItem(AvailableOptions[Key])
		]
	+ SHorizontalBox::Slot()
		.HAlign(HAlign_Right)
		[
			SNew(SCheckBox)
			.OnCheckStateChanged(this, &SGOAPAtomPin::OnCheckStateChanged)
		.IsChecked(Value)
		]

}

void SGOAPAtomPin::OnStateValueChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo)
{
	if (ItemSelected.IsValid())
	{
		// Fetches the byte index for this string from the settings class
		for (int32 i = 0; i < AvailableOptions.Num(); ++i)
		{
			if (AvailableOptions[i] == ItemSelected)
			{
				Key = GOAPSettings->GetByteKey(ItemSelected);
				
			}
		}
	}
}

void SGOAPAtomPin::OnCheckStateChanged(ECheckBoxState CheckState)
{
	if (CheckState == ECheckBoxState::Checked)
	{
		ValueHandle->SetValue(true);
	}
	else
	{
		ValueHandle->SetValue(false);
	}
}



void SetValue(uint8 aKey, bool aValue)
{
	FGOAPAtom atom = FGOAPAtom(aKey, aValue);
	GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, atom);
}

void SGOAPAtomPin::OnAttributeSelected(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo)
{
	//FString CurrentValue = GraphPinObj->GetDefaultAsString();
	FString CurrentDefaultValue = GraphPinObj->GetDefaultAsString();
	FString attribute = *ItemSelected;
	if (CurrentDefaultValue.IsEmpty())
	{
		CurrentDefaultValue = FString(TEXT("()"));
	}
	//here we construct, setter for value in struct.
	//open it with (
	FString AttributeString = TEXT("(");
	if (!attribute.IsEmpty())
	{
		//now set here proerty name from USTRUCT(), \" - will add opening "
		// so it will look like AttributeName="
		AttributeString += TEXT("AttributeName=\"");
		//add value you want to set to your property"
		AttributeString += attribute;
		//close with "
		AttributeString += TEXT("\"");
	}
	//and at last add ) so it will look like (AttributeName="Value");
	AttributeString += TEXT(")");
	//and here we set our value to parameter if it different than last one.
	if (!CurrentDefaultValue.Equals(AttributeString))
	{
		
	}
}