
#include "DawnBreakersEditorExtend.h"
#include "IDawnBreakersEditorExtend.h"



DEFINE_LOG_CATEGORY(DawnBreakersEditorExtend)
#define LOCTEXT_NAMESPACE "DawnBreakersEditorExtend"


void FDawnBreakersEditorExtend::StartupModule()
{
	UE_LOG(DawnBreakersEditorExtend, Warning, TEXT("DawnBreakersEditorExtend  Start...."));
}

void FDawnBreakersEditorExtend::ShutdownModule()
{
	UE_LOG(DawnBreakersEditorExtend, Warning, TEXT("DawnBreakersEditorExtend End...."));

}

#undef LOCTEXT_NAMESPACE
