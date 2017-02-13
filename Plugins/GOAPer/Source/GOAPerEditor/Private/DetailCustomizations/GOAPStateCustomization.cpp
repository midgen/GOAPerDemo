#include "GOAPerEditor.h"
#include "GOAPStateCustomization.h"
#include "GOAPState.h"
#include "STextComboBox.h"
#include "SCheckBox.h"
#include "../Widgets/GOAPStateWidget.h"
#include "IPropertyUtilities.h"

#define LOCTEXT_NAMESPACE "GOAPStateCustomization"


TSharedRef<IPropertyTypeCustomization> FGOAPStateCustomization::MakeInstance()
{
	return MakeShareable(new FGOAPStateCustomization());
}

void FGOAPStateCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> inStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	PropertyUtilities = StructCustomizationUtils.GetPropertyUtilities();

	StructPropertyHandle = inStructPropertyHandle;

	// Get the available options from our settings class
	for (auto& stateString : GOAPSettings->AState)
	{
		AvailableOptions.Add(MakeShareable<FString>(new FString(stateString)));
	}

	// Now fetch the handles to our child properties, and get their values
	uint32 NumChildren;
	StructPropertyHandle->GetNumChildren(NumChildren);

	for (uint32 ChildIndex = 0; ChildIndex < NumChildren; ++ChildIndex)
	{
		const TSharedPtr< IPropertyHandle > ChildHandle = StructPropertyHandle->GetChildHandle(ChildIndex);
		if (ChildHandle->GetProperty()->GetName() == TEXT("Key"))
		{
			KeyHandle = ChildHandle;
			ChildHandle->GetValue(Key);
		}
		if (ChildHandle->GetProperty()->GetName() == TEXT("Value"))
		{
			ValueHandle = ChildHandle;
			ChildHandle->GetValue(Value);
		}

	}

	SelectedString = GOAPSettings->GetStringForByte(Key);

	check(KeyHandle.IsValid());
	check(ValueHandle.IsValid());

	HeaderRow
		.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget(LOCTEXT("Extra info", "Header Name"))
		]
		.ValueContent()
		.MinDesiredWidth(500)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			[
				SAssignNew(KeyComboBox, STextComboBox)
				.OptionsSource(&AvailableOptions)
				.OnSelectionChanged(this, &FGOAPStateCustomization::OnStateValueChanged)
				.InitiallySelectedItem(MakeShareable<FString>(&SelectedString))
			]
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Right)
			[
				SAssignNew(ValueCheckBox, SCheckBox)
				.IsChecked(Value)
			]
		];


}


void FGOAPStateCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> inStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	//Create further customization here
}

void FGOAPStateCustomization::OnStateValueChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo)
{
	// Fetches the byte index for this string from the settings class
	for (int32 i = 0; i < AvailableOptions.Num(); ++i)
	{
		if (AvailableOptions[i] == ItemSelected)
		{
			KeyHandle->SetValue(GOAPSettings->GetByteKey(ItemSelected));
			
			SelectedString = GOAPSettings->GetStringForByte(Key);
		}
	}
	PropertyUtilities->RequestRefresh();
}

#undef LOCTEXT_NAMESPACE