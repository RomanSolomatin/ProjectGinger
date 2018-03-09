// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/ItemSystem/InventoryItems/EquipItem.h"
#include "ConsumableItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGINGER17_API UConsumableItem : public UEquipItem
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Consumable Class")
	TSubclassOf<class ABaseConsumable> consumableClass;

public:

};
