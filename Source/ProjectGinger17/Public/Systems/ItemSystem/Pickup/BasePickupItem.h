// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/ItemSystem/WorldItem.h"
#include "ItemSystem/Interfaces/IPickup.h"
#include "BasePickupItem.generated.h"

/**
 * A BasePickupItem is generic or assorted type of World Items with
 * pickup capabilities.
 */
UCLASS(Abstract, Blueprintable)
class PROJECTGINGER17_API ABasePickupItem : public AWorldItem, public IPickup
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pickup Item Properties", meta=(UIMin = "1", UIMax = "255"))
	uint8 amount;

	bool bCanBePicked;

public:

	// Interface implementation for IPickup
	virtual bool Pickup_Implementation(AActor* instigator) override;

	// Set whether the item can be picked up or not.
	virtual void SetCanBePicked_Implementation(bool _canBePicked) override;

	// Returns true if the item can be picked up. False otherwise.
	virtual bool GetCanBePicked_Implementation() override;

};
