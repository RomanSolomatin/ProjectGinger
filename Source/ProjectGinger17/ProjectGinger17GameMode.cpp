// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ProjectGinger17GameMode.h"
#include "ProjectGinger17Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Characters/Controllers/BaseDotaController.h"
#include "Characters/BaseDotaPlayer.h"

AProjectGinger17GameMode::AProjectGinger17GameMode()
{
	/*/
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	*/

	static ConstructorHelpers::FClassFinder<ABaseDotaCharacter> PlayerPawnBPClass(TEXT("/Game/DotaX/DotaPlayer"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Overrides the Default PlayerController with out custom controller.
	static ConstructorHelpers::FClassFinder<ABaseDotaController> ControllerClass(TEXT("/Game/DotaX/DotaController"));
	if (ControllerClass.Class != NULL)
	{
		PlayerControllerClass = ControllerClass.Class;
	}
	else
	{
		PlayerControllerClass = ABaseDotaController::StaticClass();
	}

}
