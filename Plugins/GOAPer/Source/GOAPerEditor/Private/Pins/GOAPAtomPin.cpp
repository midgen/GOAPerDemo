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
	 return SNew(SHorizontalBox)
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
		];

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
		Value = true;
	}
	else
	{
		Value = false;
	}
	SetValue(Key, Value);
}



void SGOAPAtomPin::SetValue(uint8 aKey, bool aValue)
{
	FGOAPAtom atom = FGOAPAtom(aKey, aValue);

	FString strKey;
	strKey.AppendInt(aKey);

	FString KeyString = TEXT("(");

		//now set here proerty name from USTRUCT(), \" - will add opening "
		// so it will look like AttributeName="
		KeyString += TEXT("Key=\"");
		//add value you want to set to your property"
		KeyString += strKey;
		//close with "
		KeyString += TEXT("\"");
	
	//and at last add ) so it will look like (AttributeName="Value");
	KeyString += TEXT(")");



	GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, KeyString);

	FString ValueString = TEXT("(");

		//now set here proerty name from USTRUCT(), \" - will add opening "
		// so it will look like AttributeName="
		ValueString += TEXT("Value=\"");
		//add value you want to set to your property"
		ValueString += aValue ? TEXT("true") : TEXT("false");
		//close with "
		ValueString += TEXT("\"");
	
	//and at last add ) so it will look like (AttributeName="Value");
	ValueString += TEXT(")");



	GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, ValueString);

}
