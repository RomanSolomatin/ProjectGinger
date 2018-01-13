// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemSystem/Pickup/BasePickupItem.h"


bool ABasePickupItem::Pickup_Implementation(AActor* instigator)
{
	// Try and acquire an Inventory item from the instigator. If none was found,
	// the instigator is an actor that has no pickup capabilities.
	UBaseInventory* playerInventory = instigator->FindComponentByClass<UBaseInventory>();

	if (playerInventory != NULL)
	{
		// Try adding the item information to the player's inventory.
		bool success = playerInventory->TryAddItemByInfo(GetBaseItemInfo(), amount);

		// Kill the Item if addition is successful.
		if (success)
		{
			UE_LOG(LogTemp, Warning, TEXT("Picked Up"));
			RemoveItem();
			return true;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Could not Pickup"));
	return false;
}

void ABasePickupItem::SetCanBePicked_Implementation(bool _canBePicked)
{
	bCanBePicked = _canBePicked;
}

bool ABasePickupItem::GetCanBePicked_Implementation()
{
	return bCanBePicked;
}



