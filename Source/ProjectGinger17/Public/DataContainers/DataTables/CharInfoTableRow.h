// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "HeroData/HeroStatsData.h"
#include "HeroData/HeroAttackData.h"
#include "HeroData/HeroRegenData.h"
#include "CharInfoTableRow.generated.h"

/**
 * CharacterInfo Table Row
 * Represents a row entry in the Hero Data Table.
 * Contains default variables and stats for each respective hero in the game.
 * The key of the data table would be the hero's name.
 */
USTRUCT(BlueprintType)
struct FCharInfoTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Character Information")
		FName displayName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Character Information")
		UTexture2D* characterPortrait;

	/* Hero Stats & Attributes */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Character Stats")
	FHeroStatsData stats;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Character Stats")
	FHeroAttackData attack;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Character Stats")
	FHeroRegenData regen;

	// Default Constructor
	FCharInfoTableRow()
	{
		stats.armor = 0;
		stats.healthPool = 300;
		stats.manaPool = 100;
		stats.moveSpeed = 450;
		stats.magicResistance = 25;

		attack.attackSpeed = 25;
		attack.baseDamage = 40;
		attack.bonusDamage = 0;
		
		regen.healthRegen = 0.1;
		regen.manaRegen = 0.05;
	}


};


UENUM(BlueprintType)
enum class ECharacterIds : uint8
{Windranger, DrowRanger, CrystalMaiden, Lina, Luna, Mirana};