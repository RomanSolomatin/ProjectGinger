// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Characters/Inventory/InventorySlot.h"
#include "ItemSystem/InventoryItem.h"
#include "BaseInventory.generated.h"

UENUM(BlueprintType)
enum class EInventoryType : uint8
{
	Backpack, Equippables, Gestures, Interactions
};

/*
* Inventory Class : Actor Component
* Attached to player, adds a TMAP to act as an inventory/container
* for the player's items. Encapsulates item information in FInventorySlot structs.
* Recall eventhough the TMAP is a pass by value, the Inventory needs to be accessed by a 
* pointer in order to modify that specific associated TMAP.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTGINGER17_API UBaseInventory : public UActorComponent
{
	GENERATED_BODY()
/// DEFAULT METHODS:
public:	
	// Sets default values for this component's properties
	UBaseInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	//UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Base Inventory")

	// The Inventory Data Structure
	// Maps the Item's Row Name to an associated Inventory Slot value
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Base Inventory")
	TArray<FInventorySlot> mainInventory;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotUpdated, int, SlotIndex);

	// Returns true if the selected index is an empty slot.
	UFUNCTION(BlueprintCallable, Category = "Base Inventory")
	virtual bool IsSlotEmpty(int index);

	// Set the selected inventory slot to the passed value and invoke the inventory updated event.
	UFUNCTION(BlueprintCallable, Category = "Base Inventory")
	virtual bool SetInventorySlot(const FInventorySlot slot, int index);

	// Iterate through the array to find the next EmptySlot in the array.
	UFUNCTION(BlueprintCallable, Category = "Base Inventory")
	virtual int FindNextEmptySlot();

	// Iterate through the array and check if a similar slot exits (while asserting it is not maximum).
	// If no similar slot is found, returns the next available empty slot.
	UFUNCTION(BlueprintCallable, Category = "Base Inventory")
	virtual int FindNextSlotFor(const FInventorySlot slot);

	// Attempts to add an item directly by searching for an existing similar entry.
	// Handles stack size manipulation.
	UFUNCTION(BlueprintCallable, Category = "Base Inventory")
	virtual bool TryAddItem(FInventorySlot _itemToAdd);

	// Overload of Add function that takes the ItemInfo and amount. Generate a slot
	// using Factory methods and calls TryAddItem.
	UFUNCTION(BlueprintCallable, Category = "Base Inventory")
	virtual bool TryAddItemByInfo(const FBaseItemInfo _itemInfo, uint8 _amount = 1);

	// Removes an item slot occupied at the specified index.
	UFUNCTION(BlueprintCallable, Category = "Base Inventory")
	virtual bool TryRemoveItem(int index);

	virtual void MergeSlots(FInventorySlot& _slotToAdd, FInventorySlot& _slotAddTo);
	int FindSimilarSlot(const FInventorySlot _slot);

	// Event to be Invoked when an item is added, changed, or removed from the inventory.
	UPROPERTY( BlueprintAssignable, Category = "Base Inventory")
	FOnInventoryUpdated InventoryUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Base Inventory")
	FOnSlotUpdated SlotUpdated;
};
