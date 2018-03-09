// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/ItemSystem/Factory/ItemFactory.h"
//#include "Inventory/InventorySlot.h"
#include "ItemSystem/InventoryItems/EquipItem.h"
#include "ItemSystem/InventoryItems/UseItem.h"
#include "ItemSystem/Weapons/BaseWeapon.h"
#include "ItemSystem/Consumables/BaseConsumable.h"
#include "DataContainers/DataTables/WeaponTableRow.h"
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
	ConstructorHelpers::FObjectFinder<UDataTable> itemTableObj (TEXT("DataTable'/Game/DotaX/ItemTable_A.ItemTable_A'"));
	if (itemTableObj.Succeeded())
	{
		itemTable = itemTableObj.Object;
	}

	// Search our assets for a WeaponDataTable. If found, assign the weaponTable variable to it.
	ConstructorHelpers::FObjectFinder<UDataTable> weaponTableObj(TEXT("DataTable'/Game/DotaX/WeaponTable.WeaponTable'"));
	if (weaponTableObj.Succeeded())
	{
		weaponTable = weaponTableObj.Object;
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

	if (weaponTable == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon Table was not found!"));
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

ABaseGameItem * AItemFactory::CreateGameItem(FName _itemRowName, AActor * _instigator)
{
	FItemTableRow* iteminfo = GetItemInfo(_itemRowName);

	// Do NOT allow the spawning of the actor without a proper instigator.
	// We need to access the specific instance of UWorld from the instigator.
	if (!_instigator)
	{
		UE_LOG(LogTemp, Warning, TEXT("CreateWorldItem: Failed to create instance of item because no proper Instigator was provided."));
		return NULL;
	}

	if (iteminfo)
	{
		UClass* itemClass = iteminfo->ItemClass.Get();

		if (!itemClass) { UE_LOG(LogTemp, Warning, TEXT("CreateGameItem: Failed to create instance of item. Item has no Item Class Type.")); return NULL; }


		/* Spawning */
		ABaseGameItem* spawnedItem = _instigator->GetWorld()->SpawnActor<ABaseGameItem>(itemClass);

		/* Post-Spawn */
		spawnedItem->SetItemRowName(_itemRowName);
		spawnedItem->SetItemName(iteminfo->ItemName);
		spawnedItem->SetItemDescription(iteminfo->ItemDescription);

		/* Sub Class Initialization */
		HandleSubClassInit(spawnedItem, iteminfo);

		return spawnedItem;
	}

	return nullptr;
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

	slot.itemCategory = itemInfo.inventoryCategory;
	
}



/*
// * Given an InventoryItem, initialize and assemble the item based
// * on the info found in the item table row.
*/
FORCEINLINE void AItemFactory::HandleInventoryItemInit(UInventoryItem* item, FItemTableRow* itemInfo)
{

}

/*	Handle Subclass Init
*	
*	Second stage of item construction. Determines the sub class of game items the object belongs to.
*	Initializes class specific parameters for the item. The calling method then returns the finished, initialized object.
*
*	@Params ABaseGameItem*:	A reference to the pointer of the item being initialized.
*	@Params FItemTableRow*:	A reference to the item table row entry that contains the item information.
*/
FORCEINLINE void AItemFactory::HandleSubClassInit(ABaseGameItem* &item, FItemTableRow * itemInfo)
{
	// Handle Initialization Weapon Parameters
	if (item->IsA(ABaseWeapon::StaticClass()))
	{
		FWeaponTableRow* weaponInfo = weaponTable->FindRow<FWeaponTableRow>(item->GetItemRowName(), FString(""), true);

		if (weaponInfo)
		{
			UE_LOG(LogTemp, Warning, TEXT("ItemFactory: Initializing Weapon Info"));
			((ABaseWeapon*)item)->SetDamage(weaponInfo->Damage);
			((ABaseWeapon*)item)->SetPreAttackTime(weaponInfo->PreAttackTime);
			((ABaseWeapon*)item)->SetPostAttackTime(weaponInfo->PostAttackTime);
			((ABaseWeapon*)item)->SetWeaponDamageType(weaponInfo->DamageType);
			((ABaseWeapon*)item)->SetWeaponMesh(weaponInfo->WeaponMesh.LoadSynchronous());
			((ABaseWeapon*)item)->SetWeaponModifiers(weaponInfo->WeaponModifiers);
		}
	}

	// Handle Initialization of Consumable Parameters
	if (item->IsA(ABaseConsumable::StaticClass()))
	{

	}

	// Handle Initialization of World Item Parameters
	if (item->IsA(AWorldItem::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemFactory: Initializing WorldItem Info"))
		((AWorldItem*)item)->SetItemName(itemInfo->ItemName);
		((AWorldItem*)item)->SetItemDescription(itemInfo->ItemDescription);
		((AWorldItem*)item)->SetItemMesh(itemInfo->ItemMesh);
		((AWorldItem*)item)->SetItemCollisionBox(itemInfo->collisionBoxSize);
		((AWorldItem*)item)->SetItemMaterial(itemInfo->ItemMaterial);
	}

}
#pragma endregion


