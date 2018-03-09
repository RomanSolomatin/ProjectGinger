// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemSystem/InventoryItem.h"

UInventoryItem::UInventoryItem()
{
}

FName UInventoryItem::ItemRowName() const
{
	return itemRowName;
}

void UInventoryItem::SetItemRowName(FName _itemRowName)
{
	itemRowName = _itemRowName;
}
