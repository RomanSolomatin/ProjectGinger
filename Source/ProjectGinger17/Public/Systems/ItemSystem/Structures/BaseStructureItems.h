// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Systems/ItemSystem/WorldItem.h"
#include "DataContainers/DamageData.h"
#include "math.h"
#include "BaseStructureItems.generated.h"

/**
 * Base Structure Items - Inherits WorldItem
 * This class establishes basic properties of structural items in game.
 * It is responsible for providing health, damage intake, and placement event functionalities.
 */
UCLASS(BlueprintType)
class PROJECTGINGER17_API ABaseStructureItems : public AWorldItem
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Structure Properties")
		float itemTotalHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Structure Properties")
		float itemHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Structure Properties")
		bool invulnerable;

	// Default Constructor
	ABaseStructureItems();

	UFUNCTION(BlueprintCallable, Category = "Structure Methods")
		void InflictDamage(FDamageData damageData);

	UFUNCTION(BlueprintCallable, Category = "Structure Methods")
		void InflictRawDamage(float damage);

	// Handles the destruction of a structure. Spawns debris and plays appropriate sounds.
	UFUNCTION(BlueprintCallable, Category = "Structure Methods")
		virtual void DestroyStructure();

	
};
