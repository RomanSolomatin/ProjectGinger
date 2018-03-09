// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Systems/ItemSystem/InventoryItem.h"
#include "Characters/CharacterConstants.h"
#include "Engine/SkeletalMesh.h"
#include "EquipItem.generated.h"


/**
 *	Base Class for inventory items that can be equipped to the player.
 *	Specifies which socket location in the character skeleton the item
 *	will snap to.
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTGINGER17_API UEquipItem : public UInventoryItem
{
	GENERATED_BODY()
	
protected:

	/* Stores the socket names in the character's skeleton
	*  by ID numbers.
	* @ Id 1 = Left Hand
	* @ Id 2 = Right Hand
	* @ Id 3 = Back
	*/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Equip Item")
	ECharacterSockets socketId;
	
	// The display mesh of this item in the player's hand when equipped.
	//UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Equip Item")
	//TAssetPtr<USkeletalMesh> itemMesh;

public:

	//TAssetPtr<USkeletalMesh> GetItemVisualMesh() const;
	ECharacterSockets GetItemSocket() const;

	//void SetItemVisualMesh(TAssetPtr<USkeletalMesh> _itemMesh);
	void SetItemSocket(ECharacterSockets _socket);
	
};

/* NOTE TO SELF */
/* 
 INTERFACES NEED to be declared as BlueprintNative/Implementable events if they are
 to be used in the editor. In the implementing class, use the virtual - override specifiers
 while ensuring the function name is suffixed by _Implementation. If the interface is not to be 
 used in blueprints, use a class specifier to notify UHT and ensure the interface methods are declared
 as virtual. https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/Reference/Interfaces/
*/