// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Systems/ItemSystem/InventoryItem.h"
#include "ItemSystem/Interfaces/Equippable.h"
#include "Engine/SkeletalMesh.h"
#include "EquipItem.generated.h"

// Convenient and Safe handling for Socket Name IDs
UENUM(BlueprintType)
enum class ECharacterSockets : uint8
{
	LeftHand = 0, RightHand = 1, Back = 2
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class PROJECTGINGER17_API UEquipItem : public UInventoryItem, public IEquippable
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
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Equip Item")
	UStaticMesh* itemMesh;
	
public:

	// Handles spawning the equippable actor and spawning it in the world
	virtual void Equip_Implementation(AActor* instigator) override;

	// Handles despawning the equippable actor
	virtual void DeEquip_Implementation(AActor* instigator) override;
	
	
};

/* NOTE TO SELF */
/* 
 INTERFACES NEED to be declared as BlueprintNative/Implementable events if they are
 to be used in the editor. In the implementing class, use the virtual - override specifiers
 while ensuring the function name is suffixed by _Implementation. If the interface is not to be 
 used in blueprints, use a class specifier to notify UHT and ensure the interface methods are declared
 as virtual. https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/Reference/Interfaces/
*/