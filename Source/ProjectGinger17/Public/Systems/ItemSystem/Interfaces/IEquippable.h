// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IEquippable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEquippable : public UInterface
{
	GENERATED_BODY()
};

/** IEquippable
 * An interface for all objects that exhibit equippable
 * functionalities.
 */
class PROJECTGINGER17_API IEquippable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Equip Item")
	void OnEquipped();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Equip Item")
	void OnDeEquipped();
	
};
