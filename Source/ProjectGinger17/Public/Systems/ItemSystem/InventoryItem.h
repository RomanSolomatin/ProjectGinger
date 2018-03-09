// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItem.generated.h"

/**
 * Inventory Item Actor Component
 * An attachable component that represent an
 * active item held by the player.
 */
UCLASS(Abstract)
class PROJECTGINGER17_API UInventoryItem : public UObject
{
	GENERATED_BODY()

public:
	
	UInventoryItem();

	FName ItemRowName() const;
	void SetItemRowName(FName _itemRowName);
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item")
	FName itemRowName;

};
