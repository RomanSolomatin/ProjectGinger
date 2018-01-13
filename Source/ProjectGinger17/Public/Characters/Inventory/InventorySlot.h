// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataContainers/BaseItemInfo.h"
#include "InventorySlot.generated.h"

UENUM(BlueprintType, meta = (Bitflags))
enum class EItemCategory : uint8
{ 
	Resource 	UMETA(DisplayName = "Resource") ,
	Equip 		UMETA(DisplayName = "Equip"),
	Use			UMETA(DisplayName = "Use"),
	Key			UMETA(DisplayName = "Key")
};
ENUM_CLASS_FLAGS(EItemCategory);

/**
 * Inventory Slot
 * A Structure that wraps inventory items to be placed
 * in the player's inventory. Manages UI aspects of inventory items
 * such as item stack count and icon.
 */
USTRUCT(BlueprintType)
struct FInventorySlot
{
public:
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Slot")
	FBaseItemInfo itemInfo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Slot", meta = (Bitmask, BitmaskEnum = "EItemCategory"))
	uint8 itemCategory;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Slot")
	uint8 itemQuantity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Slot")
	uint8 itemMaxStackSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Slot")
	UTexture2D* itemIcon;

	// Default Constructor
	FInventorySlot()
	{
		*this = EmptySlot();
		/*
		itemInfo = FBaseItemInfo();
		itemCategory = EItemCategory::Basic;
		itemQuantity = 1;
		itemMaxStackSize = 64;
		itemIcon = NULL;
		*/
	}


	// Constructor Overload:
	// Creates a default Inventory Slot with the specified Item Info.
	FInventorySlot(const FBaseItemInfo _itemInfo)
	{
		itemInfo = _itemInfo;
		itemCategory = (uint8)EItemCategory::Resource;
		itemQuantity = 1;
		itemMaxStackSize = 64;
		itemIcon = NULL;
	}


	// Constructor Overload:
	// Creates a default Inventory Slot with the specified Item Info.
	FInventorySlot(const FBaseItemInfo _itemInfo, uint8 category)
	{
		itemInfo = _itemInfo;
		itemCategory = category;
		itemQuantity = 1;
		itemMaxStackSize = 64;
		itemIcon = NULL;
	}

	// Constructor Overload:
	// Creates an Inventory Slot with the specified Item Info, Maximum Stack Size, and Icon.
	FInventorySlot(const FBaseItemInfo _itemInfo, uint8 _itemMaxStackSize, UTexture2D* _itemIcon)
	{
		itemInfo = _itemInfo;
		itemQuantity = 1;
		itemMaxStackSize = _itemMaxStackSize;
		itemIcon = _itemIcon;
	}

	// Constructor Overload:
	// Creates an Inventory Slot with the specified Item Info, initial Quantity, Maximum Stack Size, and Icon.
	FInventorySlot(const FBaseItemInfo _itemInfo, uint8 _itemQuantity, uint8 _itemMaxStackSize, UTexture2D* _itemIcon)
	{
		itemInfo = _itemInfo;
		itemQuantity = itemQuantity;
		itemMaxStackSize = _itemMaxStackSize;
		itemIcon = _itemIcon;
	}

	// [TESTING] Function variant of the == operator
	bool IsSameItem(const FInventorySlot& other)
	{
		return(itemInfo.itemRowName == other.itemInfo.itemRowName);
	}

	const static FInventorySlot EmptySlot()
	{
		FInventorySlot empty{ FBaseItemInfo()};
		empty.itemInfo.itemRowName == "NULL";
		return empty;
	}
	
	// Returns true if items are of the same type using their ID
	FORCEINLINE bool operator==(const FInventorySlot& other)
	{
		return(itemInfo.itemRowName == other.itemInfo.itemRowName);
	}

	// Returns the difference in item quantities.
	FORCEINLINE uint8 operator-(const FInventorySlot& other)
	{
		return FMath::Abs(other.itemQuantity - itemQuantity);
	}

	// Returns the sum of item quantities
	FORCEINLINE uint8 operator+(const FInventorySlot& other)
	{
		return other.itemQuantity + itemQuantity;
	}
};
