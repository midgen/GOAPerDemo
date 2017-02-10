#include "GOAPerEditor.h"
#include "GOAPStateCustomization.h"
#include "GOAPState.h"
#include "../Widgets/GOAPStateWidget.h"

#define LOCTEXT_NAMESPACE "GOAPStateCustomization"


TSharedRef<IPropertyTypeCustomization> FGOAPStateCustomization::MakeInstance()
{
	return MakeShareable(new FGOAPStateCustomization());
}

void FGOAPStateCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	uint32 NumChildren;
	StructPropertyHandle->GetNumChildren(NumChildren);

	for (uint32 ChildIndex = 0; ChildIndex < NumChildren; ++ChildIndex)
	{
		const TSharedRef< IPropertyHandle > ChildHandle = StructPropertyHandle->GetChildHandle(ChildIndex).ToSharedRef();

		if (ChildHandle->GetProperty()->GetName() == TEXT("State"))
		{
			// Got the IPropertyHandleMap
			StateUPropertyHandle = ChildHandle->AsMap();
			// got the UMapProperty
			StateUProperty = Cast<UMapProperty>(ChildHandle->GetProperty());

			FScriptMapHelper ScriptMapHelper(StateUProperty.Get(), !!!MapValuePtr!!!);

			const int32 ElementCount = ScriptMapHelper.Num();

			for (int32 j = 0; j < ElementCount; ++j)
			{

			}

		}
	}

	check(StateUPropertyHandle.IsValid());


	HeaderRow.NameContent()
		[
			//StructPropertyHandle->CreatePropertyNameWidget(TEXT("New property header name"), false)
			StructPropertyHandle->CreatePropertyNameWidget()
		]
	.ValueContent()
		.MinDesiredWidth(500)
		[
			//SNew(STextBlock)
			//.Text(LOCTEXT("Extra info", "Some new representation"))
			//.Font(IDetailLayoutBuilder::GetDetailFont())
			SNew(SGOAPStateWidget).GOAPStateHandle(StateUPropertyHandle)

		];


}

void FGOAPStateCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	//Create further customization here
}

#undef LOCTEXT_NAMESPACE