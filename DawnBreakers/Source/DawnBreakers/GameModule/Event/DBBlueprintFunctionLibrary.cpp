// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBBlueprintFunctionLibrary.h"
#include "GameModule/Event/EventSets.h"




UEventSets* UDBBlueprintFunctionLibrary::GetEventSets()
{
	return UEventSets::Instance();
}
