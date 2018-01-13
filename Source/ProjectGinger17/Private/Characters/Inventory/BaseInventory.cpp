// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Inventory/BaseInventory.h"
#include "Systems/GameSettings/DotaGameInstance.h"

/// DEFAULT METHODS:
// Sets default values for this component's properties
UBaseInventory::UBaseInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	mainInventory.Init(FInventorySlot::EmptySlot(), 24);
}


// Called when the game starts
void UBaseInventory::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Error, TEXT("Array Capacity: %i"), mainInventory.Max());

	UE_LOG(LogTemp, Error, TEXT("Array Elements: %i"), mainInventory.Num());
}


// Called every frame
void UBaseInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


bool UBaseInventory::IsSlotEmpty(int index)
{
	if (index > mainInventory.Max() || index < 0)
	{
		return false;
	}

	return(mainInventory[index] == FInventorySlot::EmptySlot());
}


// Set the value of a slot index with the provided FInventory.
bool UBaseInventory::SetInventorySlot(const FInventorySlot slot, int index)
{
	if (index > mainInventory.Max() || index < 0)
	{
		return false;
	}
	else
	{
		mainInventory[index] = slot;
		InventoryUpdated.Broadcast();
		SlotUpdated.Broadcast(index);
		return true;
	}
}


// Find the next available empty inventory slot.
int UBaseInventory::FindNextEmptySlot()
{
	for (int i = 0; i < mainInventory.Max(); i++)
	{
		if(mainInventory[i] == FInventorySlot::EmptySlot())
		{
			return i;
		}
	}

	return INDEX_NONE;
}


// Find the next available slot to place an item. If slot is stackable, the function
// will return the first slot of the same item type that is not MAX ALLOTED. Otherwise
// returns the next empty slot.
int UBaseInventory::FindNextSlotFor(const FInventorySlot slot)
{
	int index = -1;
	UE_LOG(LogTemp, Error, TEXT("Array Capacity: %i"), mainInventory.Max());

	UE_LOG(LogTemp, Error, TEXT("Array Elements: %i"), mainInventory.Num());

	// Item is stackable. Attempt to search for an identical item to superimpose them.
	if (slot.itemMaxStackSize > 1)
	{
		index = FindSimilarSlot(slot);
		UE_LOG(LogTemp, Warning, TEXT("Item is Stackable, Search for Duplicated returned Index: %i"), index);
		if (index != INDEX_NONE)
		{
			return index;
		}
	}

	// If the above fails to pass, then we need to find the next empty slot.
	index = FindNextEmptySlot();
	UE_LOG(LogTemp, Warning, TEXT("Search for EmptySlot returned Index: %i"), index);

	if (index == INDEX_NONE)
	{
		UE_LOG(LogTemp, Error, TEXT("Array Capacity: %i"), mainInventory.Max());

		UE_LOG(LogTemp, Error, TEXT("Array Elements: %i"), mainInventory.Num());

	}

	// Finally Return INDEX_NONE if all fails.
	return index;
}


// Givem two slots being merged, superimpose their quantities while maintaining
// their MaxStackSize constraint.
void UBaseInventory::MergeSlots(FInventorySlot & _slotToAdd, FInventorySlot & _slotAddTo)
{
	UE_LOG(LogTemp, Warning, TEXT("Before Merge, Adding Item Quanity = %i ; AddedTo Quantity = %i"), _slotToAdd.itemQuantity, _slotAddTo.itemQuantity);
	uint8 quantityBeforeMerge = _slotAddTo.itemQuantity;

	_slotAddTo.itemQuantity = FMath::Clamp((uint8)(_slotAddTo.itemQuantity + _slotToAdd.itemQuantity), (uint8)0, _slotAddTo.itemMaxStackSize);

	UE_LOG(LogTemp, Warning, TEXT("AddedTo NEW Quantity = %i"), _slotAddTo.itemQuantity);
	// Set the Adding Slot quantity to whatever remains. Will always be >= 0.
	_slotToAdd.itemQuantity -= (_slotAddTo.itemQuantity - quantityBeforeMerge);

	UE_LOG(LogTemp, Warning, TEXT("Adding Item NEW Quantity = %i"), _slotToAdd.itemQuantity);
}


// Attempts to find the next available index of an item slot with 
// the same ID.
int UBaseInventory::FindSimilarSlot(const FInventorySlot _slot)
{
	for (int i = 0; i < mainInventory.Max(); i++)
	{
		if((mainInventory[i].itemInfo.itemRowName == _slot.itemInfo.itemRowName) && (mainInventory[i].itemQuantity < _slot.itemMaxStackSize))
		{
			return i;
		}
	}

	return INDEX_NONE;
}


bool UBaseInventory::TryAddItem(FInventorySlot _itemToAdd)
{
	// Use an EmptySlot as indication for null values.
	// Do not add if we are given an Empty item.
	if (_itemToAdd == FInventorySlot::EmptySlot())
	{
		return false;
	}

	int index = FindNextSlotFor(_itemToAdd);
	UE_LOG(LogTemp, Warning, TEXT("Return Index: %i"), index);

	if (index == INDEX_NONE) { return false; }

	if (mainInventory[index] == _itemToAdd)
	{
		// Merge the identitical slots' quantities first.
		MergeSlots(_itemToAdd, mainInventory[index]);
		UE_LOG(LogTemp, Warning, TEXT("MergeSlot:Called"));

		// Is there any remaining quantity that didn't fit into the stack?
		// If so, try re-adding the remainders.
		if (_itemToAdd.itemQuantity > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("ReAdd: Called"));
			return TryAddItem(_itemToAdd);
		}

		// Otherwise we are done. Return true to indicate operation success.
		else
		{
			InventoryUpdated.Broadcast();
			SlotUpdated.Broadcast(index);
			return true;
		}
		
	}

	// The slot is empty. Emplace the passed slot into place directly.
	else if(mainInventory[index] == FInventorySlot::EmptySlot())
	{
		return SetInventorySlot(_itemToAdd, index);
	}
	
	// Weed occured - ABORT!
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BaseInventory: TryAddItem failed with a weed Exception!"));
		return false;
	}
}


bool UBaseInventory::TryAddItemByInfo(FBaseItemInfo _itemInfo, uint8 _amount)
{
	UDotaGameInstance* gameInstance = Cast<UDotaGameInstance>(GetOwner()->GetGameInstance());

	if (!gameInstance)
	{
		return false;
	}

	if (gameInstance->ItemFactory)
	{
		FInventorySlot slotToAdd = gameInstance->ItemFactory->CreateInventorySlot(_itemInfo.itemRowName, _amount);

		return TryAddItem(slotToAdd);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TryAddItemByInfo: Failed to add specified item because the ItemFactory was not found."));
		return false;
	}
}



bool UBaseInventory::TryRemoveItem(int index)
{
	if (index > mainInventory.Max() || index < 0)
	{
		return false;
	}

	mainInventory[index] = FInventorySlot::EmptySlot();
	InventoryUpdated.Broadcast();

	return true;
}

