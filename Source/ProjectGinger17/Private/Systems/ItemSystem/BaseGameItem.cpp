// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/ItemSystem/BaseGameItem.h"

///<Summary>
/// Inherited Functions
///</Summary>

// Sets default values
ABaseGameItem::ABaseGameItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ABaseGameItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseGameItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


/// Accessor Functions
FName ABaseGameItem::GetItemRowName()
{
	return itemInfo.itemRowName;
}
FString ABaseGameItem::GetItemName()
{
	return itemInfo.itemName;
}
FString ABaseGameItem::GetItemDescription()
{
	return itemInfo.itemDescription;
}
const FBaseItemInfo ABaseGameItem::GetBaseItemInfo()
{
	return itemInfo;
}


/// Mutator Functions
void ABaseGameItem::SetItemRowName(FName _name)
{
	itemInfo.itemRowName = _name;
}
void ABaseGameItem::SetItemName(FString _name)
{
	itemInfo.itemName = _name;
}
void ABaseGameItem::SetItemDescription(FString _description)
{
	itemInfo.itemDescription = _description;
}