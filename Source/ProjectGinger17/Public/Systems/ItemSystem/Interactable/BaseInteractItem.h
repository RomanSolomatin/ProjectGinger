// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/ItemSystem/WorldItem.h"
#include "ItemSystem/Interfaces/IInteractable.h"
#include "BaseInteractItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGINGER17_API ABaseInteractItem : public AWorldItem, public IInteractable
{
	GENERATED_BODY()

	virtual void Interact_Implementation(AActor* instigator) override;
	virtual bool OnBeginInteract_Implementation(AActor* instigator) override;
	virtual bool OnEndInteract_Implementation() override;
	
};
