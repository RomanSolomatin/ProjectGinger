// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/ItemSystem/Factory/ItemFactory.h"
//#include "Inventory/InventorySlot.h"
#include "ItemSystem/InventoryItems/EquipItem.h"
#include "ItemSystem/InventoryItems/UseItem.h"
#include "Engine/World.h"

// Singleton Instance of class
static AItemFactory* _instance;

// Sets default values
AItemFactory::AItemFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Search our assets for an ItemDataTable. If found, assign the itemTable variable to it.
	// Use the Copy Reference option in the Editor to get the correct path format!
	ConstructorHelpers::FObjectFinder<UDataTable> itemTableObj (TEXT("DataTable'/Game/DotaX/ItemTable.ItemTable'"));
	if (itemTableObj.Succeeded())
	{
		itemTable = itemTableObj.Object;
	}
}

// Called when the game starts or when spawned
void AItemFactory::BeginPlay()
{
	Super::BeginPlay();

	if (itemTable == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item Table was not found!"));
	}
}

// Public Accessor for Singleton class.
AItemFactory* AItemFactory::Instance()
{
	if (_instance == NULL)
	{
		//_instance = new AItemFactory();
		_instance = NewObject<AItemFactory>();
	}

	return _instance;
}

/*
// * High Level Item Instancing Operations
*/
AWorldItem* AItemFactory::CreateWorldItem(FName _itemRowName, AActor* _instigator)
{
	FItemTableRow* itemInfo = GetItemInfo(_itemRowName);

	// Do NOT allow the spawning of the actor without a proper instigator.
	// We need to access the specific instance of UWorld from the instigator.
	if(!_instigator)
	{
		UE_LOG(LogTemp, Warning, TEXT("CreateWorldItem: Failed to create instance of item because no proper Instigator was provided."));
		return NULL;
	}

	if(itemInfo)
	{
		// Get the class template for spawning.
		UClass* itemClass = itemInfo->worldItemType.Get();

		// Verify the item entry has a World Item representation.
		if (!itemClass) { UE_LOG(LogTemp, Warning, TEXT("CreateWorldItem: Failed to create instance of item. Item has no World Class Type.")); return NULL; }
		
		// Spawns the Actor in the instigator's world. The position is in the world's center. To be
		// modified by the instigator.
		AWorldItem* spawnedItem = _instigator->GetWorld()->SpawnActor<AWorldItem>(itemClass, FTransform());
		//
		// ... Handle Initialization Here...
		HandleWorldItemInit(spawnedItem, itemInfo);
		//
		UE_LOG(LogTemp, Warning, TEXT("CreateWorldItem: Item SPAWNED!"));
		return spawnedItem;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CreateWorldItem: Failed to create instance of item. Item ID NOT found."));
		return NULL;
	}
}


/* Create Inventory Item
* Returns a fully instantiated and initialized Inventory Item for the requested Item ID.
* The Instigator is set to be the owner (Outer) of the instantiated object.
* Returns NULL if the item was not found or if no instigator was passed.
*/
UInventoryItem* AItemFactory::CreateInventoryItem(FName _itemRowName, AActor* _instigator)
{
	FItemTableRow* itemInfo = GetItemInfo(_itemRowName);
	
	// Do NOT allow the creation of the UObject if a proper outer is not provided.
	// Enforce constraint to avoid memory leaks.
	if(!_instigator)
	{
		UE_LOG(LogTemp, Warning, TEXT("CreateInventoryItem: Failed to create instance of item because no proper Instigator was provided."));
		return NULL;
	}

	if (itemInfo)
	{
		UClass* inventoryClass = itemInfo->inventoryItemType.Get();

		// Verify an Inventory Item exists for this item.
		if (!inventoryClass) { return NULL; }
		else
		{
			UInventoryItem* returnItem = NewObject<UInventoryItem>(_instigator, inventoryClass);
			//
			// ... Handle Initialization Here...
			//
			return returnItem;
		}
	}
	// Return NULL if the item was not found.
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CreateInventoryItem: Failed to create instance of item. Item ID NOT found."));
		return NULL;
	}
}


FInventorySlot AItemFactory::CreateInventorySlot(FName _itemRowName, uint8 _quantity)
{
	FItemTableRow* itemInfo = GetItemInfo(_itemRowName);

	if (itemInfo)
	{
		FInventorySlot slot = FInventorySlot();
		slot.itemInfo.itemRowName = _itemRowName;
		slot.itemQuantity = _quantity;

		// Initialize the parameters using the helper function.
		InitializeInventorySlot(slot, *itemInfo);

		return slot; 
	}
	
	// An Empty Slot resembles an invalid return type.
	else
	{
		return FInventorySlot::EmptySlot();
	}
}

/*
// * Underlying supplementary methods.
*/

// Returns a pointer to the row associated with the given row name
 FORCEINLINE FItemTableRow* AItemFactory::GetItemInfo(FName _itemRowName)
{
	 // Check if the Table exist or is Valid.
	 if (itemTable)
	 {
		 // Get the pointer to the row and dereference it for return.
		 return itemTable->FindRow <FItemTableRow>(_itemRowName, FString(""), true);
	 }
	 else
	 {
		 return NULL;
	 }
}


#pragma region INTERNAL_NATIVE_METHODS
 /*
 / * Internal native methods used to handle the initialization of the specific item.
 */

 /* Initialize the values for a passed InventorySlot reference if its
 *	information exist in the datatable.
 *	Params
 *	@FInventorySlot slot - A reference to the slot being initialized.
 */
void AItemFactory::InitializeInventorySlot(FInventorySlot &slot) 
{
	FItemTableRow* itemInfo = GetItemInfo(slot.itemInfo.itemRowName);

	// Although unlikely, verify the item exists in the datatable.
	if (itemInfo)
	{
		// Call the overloaded function to handle the initialization
		// of all member variables.
		InitializeInventorySlot(slot, *itemInfo);
	}
}

/*	Overloaded variant of InitializeInventorySlot that takes the ItemTableRow for initialization.
*	Initialize the values for a passed InventorySlot reference using the provided
*	ItemInfo. Generally speaking, non-overloaded form of the function is used for convenience
*	when external classes are attempting to initialize a slot directly without having to retrieve
*	its ItemInfo from the datatable.
*
*	Params
*	@FInventorySlot slot - A reference to the slot being initialized.
*	@FItemTableRow itemInfo - The value of the datatable row entry associated with the slot's ItemRowName.
*/
void AItemFactory::InitializeInventorySlot(FInventorySlot &slot, const FItemTableRow itemInfo)
{
	slot.itemInfo.itemName = itemInfo.ItemName;
	slot.itemInfo.itemDescription = itemInfo.ItemDescription;
	
	slot.itemIcon = itemInfo.ItemIcon;
	slot.itemMaxStackSize = itemInfo.MaxStackSize;
	slot.itemQuantity = 1;

	// Setting the category of the item based on its class. The category is used primarily by UI elements.
	if (itemInfo.inventoryItemType.Get()->IsChildOf(UUseItem::StaticClass()))
	{
		slot.itemCategory = (uint8)EItemCategory::Use | (uint8)EItemCategory::Equip;
	}
	else if (itemInfo.inventoryItemType.Get()->IsChildOf(UEquipItem::StaticClass()))
	{
		slot.itemCategory = (uint8)EItemCategory::Equip;
	}
	else
	{
		slot.itemCategory = (uint8)EItemCategory::Resource;
	}
	
}


/*	Handle World Item Init
*	Called internally by the factory method after CreateWorldItem is called.
*	This INLINE helper function sets the basic variables/information for the item.
*
*	Params
*	@AWorldItem* item - A Pointer to the item currently being modified.
*	@FItemTableRow* itemInfo - A Pointer to the ItemTableRow entry that contains the information about the World Item.
*/
FORCEINLINE void AItemFactory::HandleWorldItemInit(AWorldItem* item, FItemTableRow* itemInfo)
{
	item->SetItemName(itemInfo->ItemName);
	item->SetItemDescription(itemInfo->ItemDescription);
	item->SetItemMesh(itemInfo->ItemMesh);
	item->SetItemCollisionBox(itemInfo->collisionBoxSize);
	item->SetItemMaterial(itemInfo->ItemMaterial);
}

/*
// * Given an InventoryItem, initialize and assemble the item based
// * on the info found in the item table row.
*/
FORCEINLINE void AItemFactory::HandleInventoryItemInit(UInventoryItem* item, FItemTableRow* itemInfo)
{

}
#pragma endregion


