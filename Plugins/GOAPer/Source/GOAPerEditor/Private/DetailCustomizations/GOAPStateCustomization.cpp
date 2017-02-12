#include "GOAPerEditor.h"
#include "GOAPStateCustomization.h"
#include "GOAPState.h"
#include "GOAPerSettings.h"
#include "STextComboBox.h"
#include "SCheckBox.h"
#include "../Widgets/GOAPStateWidget.h"

#define LOCTEXT_NAMESPACE "GOAPStateCustomization"


TSharedRef<IPropertyTypeCustomization> FGOAPStateCustomization::MakeInstance()
{
	return MakeShareable(new FGOAPStateCustomization());
}

void FGOAPStateCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	UGOAPerSettings* Settings = GetMutableDefault<UGOAPerSettings>();

	for (auto& stateString : Settings->AState)
	{
		AvailableOptions.Add(MakeShareable<FString>(&stateString));
	}


	uint32 NumChildren;
	StructPropertyHandle->GetNumChildren(NumChildren);
	StateStructProperty = Cast<UStructProperty>(StructPropertyHandle->GetProperty());

	for (uint32 ChildIndex = 0; ChildIndex < NumChildren; ++ChildIndex)
	{
		const TSharedRef< IPropertyHandle > ChildHandle = StructPropertyHandle->GetChildHandle(ChildIndex).ToSharedRef();
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

	check(StateStructProperty.IsValid());


	HeaderRow.NameContent()
		[
			//StructPropertyHandle->CreatePropertyNameWidget(TEXT("New property header name"), false)
			StructPropertyHandle->CreatePropertyNameWidget()
		]
	.ValueContent()
		.MinDesiredWidth(500)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			[
				SAssignNew(KeyComboBox, STextComboBox)
				.OptionsSource(&AvailableOptions)
				.OnSelectionChanged(this, &FGOAPStateCustomization::OnStateValueChanged)
				.InitiallySelectedItem(AvailableOptions[0])
			]
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Right)
			[
				SAssignNew(ValueCheckBox, SCheckBox)
				.IsChecked(true)
			]
			
			

		];

}

void FGOAPStateCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	//Create further customization here
}


void FGOAPStateCustomization::OnStateValueChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo)
{
	for (int32 i = 0; i < AvailableOptions.Num(); ++i)
	{
		if (AvailableOptions[i] == ItemSelected)
		{
			//KeyHandle->SetValue(i);
		}
	}
}

#undef LOCTEXT_NAMESPACE