// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Systems/ItemSystem/InventoryItem.h"
#include "ItemSystem/Structures/BaseStructureItems.h"
#include "ItemTableRow.generated.h"

/**
 * Struct to hold the information layout for Item Data Table
 */
USTRUCT(BlueprintType)
struct FItemTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	/**
	// * Item Visual Properties
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Basic Info")
		FString ItemName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Basic Info")
		FString ItemDescription;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Basic Info")
		TAssetSubclassOf<AWorldItem> worldItemType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Visual Info")
		UTexture2D* ItemIcon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Visual Info")
		UStaticMesh* ItemMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Visual Info")
		FVector collisionBoxSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Visual Info")
		EItemMaterials ItemMaterial;
	
	/*
	// * Interactive Properties
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Interaction Info")
		bool isPickup;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Interaction Info")
		bool isInteract;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Interaction Info") // Interaction behaviours are all derived from the base UInteractable component.
	//	TAssetSubclassOf<UInteractable> interactableType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Interaction Info")
		bool spawnsEffect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Interaction Info")
		UParticleSystem* particleEffect;

	/*
	// * Inventory Properties
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Interaction Info")
		TAssetSubclassOf<UInventoryItem> inventoryItemType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Interaction Info")
		uint8 MaxStackSize;


	FItemTableRow()
	{
		ItemName = "";
		ItemDescription = "";
		worldItemType = NULL;
		ItemMaterial = EItemMaterials::M_Concrete;

		ItemIcon = NULL;
		ItemMesh = NULL;
		collisionBoxSize.X = 32;
		collisionBoxSize.Y = 32;
		collisionBoxSize.Z = 32;

		// Pickup Properties
		isPickup = false;
		isInteract = false;
		//interactableType = NULL;
		spawnsEffect = false;
		particleEffect = NULL;

		// Inventory Properties
		inventoryItemType = NULL;
		MaxStackSize = 1;
	}


};