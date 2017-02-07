#include "GOAPerEditor.h"
#include "GOAPState.h"
#include "DetailCustomizations/GOAPStateCustomization.h"


IMPLEMENT_GAME_MODULE(FGOAPerEditorModule, GOAPerEditor);

DEFINE_LOG_CATEGORY(GOAPerEditor)

#define LOCTEXT_NAMESPACE "GOAPerEditor"

void FGOAPerEditorModule::StartupModule()
{
	UE_LOG(GOAPerEditor, Warning, TEXT("GOAPerEditorModule: Log Started"));

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	//Custom properties
	PropertyModule.RegisterCustomPropertyTypeLayout("GOAPState", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FGOAPStateCustomization::MakeInstance));
}

void FGOAPerEditorModule::ShutdownModule()
{
	UE_LOG(GOAPerEditor, Warning, TEXT("GOAPerEditorModule: Log Ended"));
}

#undef LOCTEXT_NAMESPACE