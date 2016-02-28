// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "DawnBreakers.h"
#include "DawnBreakersGameMode.h"
#include "DawnBreakersHUD.h"
#include "DawnBreakersCharacter.h"

ADawnBreakersGameMode::ADawnBreakersGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ADawnBreakersHUD::StaticClass();
}
