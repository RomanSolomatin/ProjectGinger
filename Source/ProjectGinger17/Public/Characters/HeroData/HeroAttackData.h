// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HeroAttackData.generated.h"

/**
 * Hero Attack Data
 * Contains information about attack related statistics
 * of the hero such as damage and attack speed.
 */
USTRUCT(BlueprintType)
struct FHeroAttackData
{
	GENERATED_BODY()

public:
	FHeroAttackData()
	{
		baseDamage = 10;
		bonusDamage = 0;
		attackSpeed = 25;
	}

	// Hero Attack Information
	
	// Base Damage of the hero - Determined by the primary attribute value.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Attack Data")
		float baseDamage;

	// Bonus raw damage. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Attack Data")
		float bonusDamage;

	// Attack speed that influences the attacks per second the hero can execute.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Attack Data")
		float attackSpeed;
};
