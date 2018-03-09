// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemSystem/InventoryItems/EquipItems/Weapon.h"
#include "Characters/BaseDotaCharacter.h"

UWeapon::UWeapon()
{
	socketId = ECharacterSockets::RightHand;
	spawnedWeapon = NULL;
}



bool UWeapon::Drop_Implementation()
{
	// Destroy the Weapon Actor...

	// Remove the Slot from the Inventory...
	return false;
}




void UWeapon::OnEquippedCharacter()
{
}

void UWeapon::OnDeEquippedCharacter()
{
}



