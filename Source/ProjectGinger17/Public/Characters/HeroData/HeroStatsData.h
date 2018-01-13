// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HeroStatsData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FHeroStatsData
{
	GENERATED_BODY()
public:
	FHeroStatsData() {}

	// The Total Health of the Hero.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Stats Data")
	float healthPool;

	// The Total Mana Pool of the Hero.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Stats Data")
	float manaPool;

	// Physical Armor associated with the hero. Reduces the effects of physical attacks.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Stats Data")
	float armor;

	// Magical Resistance/Armor associated with the hero. Reduces the effects of magical spells.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Stats Data")
	float magicResistance;

	// The maximum movement speed of the Hero. Used as the capped velocity of the character movement component.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Stats Data")
	int moveSpeed;
};
