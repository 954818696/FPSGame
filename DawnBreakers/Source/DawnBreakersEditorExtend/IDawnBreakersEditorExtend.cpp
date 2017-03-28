
#include "DawnBreakersEditorExtend.h"
#include "IDawnBreakersEditorExtend.h"

#include "DBDetailsCustomization/DBDetailsCustomization.h"



DEFINE_LOG_CATEGORY(DawnBreakersEditorExtend)
#define LOCTEXT_NAMESPACE "DawnBreakersEditorExtend"


void FDawnBreakersEditorExtend::StartupModule()
{
	UE_LOG(DawnBreakersEditorExtend, Warning, TEXT("DawnBreakersEditorExtend  Start...."));
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout("DBWeaponBase", FOnGetDetailCustomizationInstance::CreateStatic(&FDBDetailsCustomization::MakeInstance));
}

void FDawnBreakersEditorExtend::ShutdownModule()
{
	UE_LOG(DawnBreakersEditorExtend, Warning, TEXT("DawnBreakersEditorExtend End...."));

}

#undef LOCTEXT_NAMESPACE
