// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Characters/Inventory/BaseInventory.h"
#include "IPickup.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UPickup : public UInterface
{
	GENERATED_BODY()
};

/**
 * The IPickup Interface is implemented by any world game object
 * that exhibits pick up functionalities. Actors with the interaction
 * abilities will highlight and pickup the objects regardless of their type
 * so long as they recognize this interface.
 */
class PROJECTGINGER17_API IPickup
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	// The following methods are implemented by the Pickup Placeable Actor Component.
	// The component always retrieves the owning Actor and performs a validity check before 
	// executing the operations below.

	// Picks up the object, effectively killing the object (Use Item kill function).
	// Proceed to add the item to an inventory if exists.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pickup Object")
	bool Pickup(AActor* instigator);

	// Set whether the item can be picked up or not.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pickup Object")
	void SetCanBePicked(bool _canBePicked);

	// Returns true if the item can be picked up. False otherwise.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pickup Object")
	bool GetCanBePicked();
	
};
