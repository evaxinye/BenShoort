// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BenShoortGameMode.h"
#include "BenShoortHUD.h"
#include "BenShoortCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABenShoortGameMode::ABenShoortGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ABenShoortHUD::StaticClass();
}
