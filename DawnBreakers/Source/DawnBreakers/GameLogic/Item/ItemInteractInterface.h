
#pragma once

#include "ItemInteractInterface.generated.h"

UINTERFACE()
class UItemInteractInterface : public UInterface
{
    GENERATED_UINTERFACE_BODY()
};

class IItemInteractInterface
{    GENERATED_IINTERFACE_BODY()

public:
	virtual void SetInteractFocus() = 0;

	virtual void LoseInteractFocus() = 0;
};