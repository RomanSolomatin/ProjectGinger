// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Systems/ItemSystem/InventoryItems/EquipItem.h"
#include "ItemSystem/Weapons/BaseWeapon.h"
#include "ItemSystem/Interfaces/IDroppable.h"
#include "Weapon.generated.h"


/**
 * Abstract Class of Equippable Item.
 * A Weapon Item that has damage properties that will be inflicted on other
 * game objects upon firing.
 *
 * Equipping the weapon is tasked to the character's equipment manager. The equipment manager
 * should handle broadcasting events regarding weapons being equipped/dequipped for the animation
 * system to listen to.
 */
UCLASS(Abstract)
class PROJECTGINGER17_API UWeapon : public UEquipItem, public IDroppable
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon Class")
	TAssetSubclassOf<ABaseWeapon> weaponClass;

	ABaseWeapon* spawnedWeapon;

public:

	// Default Constructor
	UWeapon();


	virtual bool Drop_Implementation() override;

	

protected:

	/*
	*	Handle post processing after the item is equipped. We need to:
	*	
	*	1) ...
	*	2) ...
	*	3) ...
	*/
	FORCEINLINE void OnEquippedCharacter();


	/*
	*	Handle post processing after the item is de-equipped. We need to:
	*
	*	1) ...
	*	2) ...
	*	3) ...
	*/
	FORCEINLINE void OnDeEquippedCharacter();
	
};
