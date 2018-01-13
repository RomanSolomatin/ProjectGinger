// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IWeapons.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UIWeapons : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTGINGER17_API IIWeapons
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// Issues a firing command to the weapon. Effectively launching the attack sequence
	// for either Melee or Ranged weapons. Melee weapons will depend on their associated collision mesh
	// to apply damage, whereas ranged weapons will simply launch the projectile.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon Interface")
	bool FireWeapon();
	
};
