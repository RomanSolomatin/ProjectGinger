// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory/InventorySlot.h"
#include "WardrobeManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTGINGER17_API UWardrobeManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWardrobeManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	// An array holding 
	TArray<FInventorySlot> cosmetics;
		
	
};
