#pragma once

#include "DawnBreakersEditorExtend.h"

DECLARE_LOG_CATEGORY_EXTERN(DawnBreakersEditorExtend, All, All)

class FDawnBreakersEditorExtend : public IModuleInterface
{
public:
	virtual void StartupModule() override;

	virtual void ShutdownModule() override;



};