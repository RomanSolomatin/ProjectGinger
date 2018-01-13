// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemSystem/InventoryItems/EquipItem.h"
#include "ItemSystem/Factory/ItemFactory.h"
#include "Characters/BaseDotaPlayer.h"




// Handles spawning the equippable actor and spawning it in the world
void UEquipItem::Equip_Implementation(AActor* instigator)
{
	if (Cast<ABaseDotaCharacter> (instigator))
	{
		((ABaseDotaCharacter*)instigator)->SetEquipSlot(((int)socketId), itemMesh);
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Equipping Finished!"));
}

// Handles despawning the equippable actor
void UEquipItem::DeEquip_Implementation(AActor* instigator)
{
	if (Cast<ABaseDotaCharacter>(instigator))
	{
		((ABaseDotaCharacter*)instigator)->SetEquipSlot(((int)socketId), NULL);
	}
}