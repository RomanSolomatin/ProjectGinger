// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemSystem/InventoryItems/EquipItems/Weapon.h"
#include "Characters/BaseDotaCharacter.h"

UWeapon::UWeapon()
{

}



void UWeapon::Equip_Implementation(AActor * instigator)
{
	Super::Equip_Implementation(instigator);

	if (Cast<ABaseDotaCharacter>(instigator))
	{
		((ABaseDotaCharacter*)instigator)->SetCharacterState(ECharacterStates::Combat);

		OnEquippedCharacter();
	}
}

void UWeapon::DeEquip_Implementation(AActor * instigator)
{
	Super::Equip_Implementation( instigator);

	if (Cast<ABaseDotaCharacter>(instigator))
	{
		((ABaseDotaCharacter*)instigator)->SetCharacterState(ECharacterStates::Neutral);

		OnDeEquippedCharacter();
	}
}

bool UWeapon::Drop_Implementation()
{
	return false;
}




void UWeapon::OnEquippedCharacter()
{
}

void UWeapon::OnDeEquippedCharacter()
{
}



