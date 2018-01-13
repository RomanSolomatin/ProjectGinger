// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseDotaCharacter.h"
#include "BaseDotaNPC.generated.h"

/**
 * Base Dota NPC
 * Inherits all basic in game character functionalities from the BaseDotaCharacter class
 * including stats, buff system, damage infliction and events.
 * Adds AI related behaviour and variable to drive NPCs in the game world. This includes
 * dynamic overlap shape and environment checking with influence from a priority function.
 */
UCLASS(BlueprintType)
class PROJECTGINGER17_API ABaseDotaNPC : public ABaseDotaCharacter
{
	GENERATED_BODY()
	
public:

	// Default Constructor
	ABaseDotaNPC();
	
	
	
};
