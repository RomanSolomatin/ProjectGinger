// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/ItemSystem/Structures/BaseStructureItems.h"


ABaseStructureItems::ABaseStructureItems()
{
	
}

// Evaluates and inflicts damage to the structure based on the retrieved Damage Data information.
void ABaseStructureItems::InflictDamage(FDamageData damageData)
{
	// No Damage is inflicted the item is set to be invulnerable
	if (invulnerable)
	{
		return;
	}

	// For brevity, use the Inflict Raw Damage function after evaluation our true damage value.
	InflictRawDamage(damageData.damageVal);
}

// Inflicts raw HP damage to the item.
void ABaseStructureItems::InflictRawDamage(float damage)
{
	// No Damage is inflicted the item is set to be invulnerable
	if (invulnerable)
	{
		return;
	}

	// Clamp the health value between 0 and the maximum health to avoid any errors.
	itemHealth = FMath::Clamp(itemHealth - damage, (float)0, itemTotalHealth);

	// If the sturcture's health reaches 0, destroy it.
	if (itemHealth <= 0)
	{
		DestroyStructure();
	}
}

// Handles the destruction of a structure. Spawns debris and plays appropriate sounds.
void ABaseStructureItems::DestroyStructure()
{
	Destroy();
}


