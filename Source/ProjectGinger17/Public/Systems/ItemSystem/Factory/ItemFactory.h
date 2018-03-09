// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "EngineMinimal.h"
#include "DataContainers/DataTables/ItemTableRow.h"
#include "Inventory/InventorySlot.h"
#include "ItemFactory.generated.h"


UCLASS(notplaceable)
class PROJECTGINGER17_API AItemFactory : public AActor
{
	GENERATED_BODY()

// Variable Declaration
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Database")
	UDataTable* itemTable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Database")
	UDataTable* weaponTable;

	// Sets default values for this actor's properties
	AItemFactory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

public:	

	static AItemFactory* Instance();

	/*
	// * High Level Item Instancing Operations
	*/
	UFUNCTION(BlueprintCallable, Category = "Item Factory Methods")
	ABaseGameItem* CreateGameItem(FName _itemRowName, AActor* _instigator);

	UFUNCTION(BlueprintCallable, Category = "Item Factory Methods")
	UInventoryItem* CreateInventoryItem(FName _itemRowName, AActor* _instigator);

	UFUNCTION(BlueprintCallable, Category = "Item Factory Methods")
	FInventorySlot CreateInventorySlot(FName _itemRowName, uint8 _quantity = 1);

	/*
	// * Underlying supplementary methods.
	*/

	// Returns a pointer to the row associated with the given row name
	//UFUNCTION(BlueprintCallable, Category = "Item Factory Methods")
	FORCEINLINE FItemTableRow* GetItemInfo(FName _name);


	// Initializes an InventorySlot based on the item it contains.
	// Defaults the starting quantity to 1.
	FORCEINLINE void InitializeInventorySlot(FInventorySlot &slot);
	FORCEINLINE void InitializeInventorySlot(FInventorySlot &slot, const FItemTableRow itemInfo);

private:
	FORCEINLINE void HandleInventoryItemInit(UInventoryItem* item, FItemTableRow* itemInfo);
	FORCEINLINE void HandleSubClassInit(ABaseGameItem* &item, FItemTableRow* itemInfo);
};



