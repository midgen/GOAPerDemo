#include "Editor/DetailCustomizations/Private/DetailCustomizationsPrivatePCH.h"
#include "GOAPState.h"
#pragma once

class FGOAPStateCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

private:
	TWeakObjectPtr<UStructProperty> StateStructProperty;

	TArray<TSharedPtr<FString>> AvailableOptions;

	uint8 Key;
	bool Value;


};