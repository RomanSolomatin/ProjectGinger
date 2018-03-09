// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemSystem/InventoryItems/EquipItem.h"
#include "ItemSystem/Factory/ItemFactory.h"
#include "Characters/BaseDotaPlayer.h"

//TAssetPtr<USkeletalMesh> UEquipItem::GetItemVisualMesh() const
//{
//	return itemMesh;
//}

ECharacterSockets UEquipItem::GetItemSocket() const
{
	return socketId;
}

//void UEquipItem::SetItemVisualMesh(TAssetPtr<USkeletalMesh> _itemMesh)
//{
//	itemMesh = _itemMesh;
//}

void UEquipItem::SetItemSocket(ECharacterSockets _socket)
{
	socketId = _socket;
}
