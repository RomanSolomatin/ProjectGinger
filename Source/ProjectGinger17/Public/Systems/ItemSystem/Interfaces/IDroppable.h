// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDroppable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDroppable : public UInterface
{
	GENERATED_BODY()
};

/**	Droppable Interface
 * 
 *	Gives items the ability to be dropped by the player.
 *	NOTE: Should this interface be used in the Inventory item or the Actor?
 */
class PROJECTGINGER17_API IDroppable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Droppable")
	bool Drop();
	
};
