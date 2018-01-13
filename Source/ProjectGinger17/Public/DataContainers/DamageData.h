// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "DamageData.generated.h"

UENUM(BlueprintType)
enum class EDamageTypes : uint8
{Normal, Siege, Pierce};

UENUM(BlueprintType)
enum class EDamageRange : uint8
{Melee, Range};

/**
 * Struct that contains structured information regarding a damage source.
 * Use primarily to determine the damage value and type of the owner.
 */
USTRUCT(BlueprintType)
struct FDamageData
{
	GENERATED_BODY()

public:
	
	// * A raw damage number that express that amount of health damage the source inflicts.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Data")
		float damageVal;

	// * A specifier to determine whether the damage source was melee or ranged.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Data")
		EDamageRange damageRange;

	// * A specifier to determine the damage type - i.e Normal, Siege, Pierce, etc.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Data")
		EDamageTypes damageType;

	// Default Constructor
	FDamageData()
	{
		damageVal = 1;
		damageRange = EDamageRange::Melee;
		damageType = EDamageTypes::Normal;
	}

	// Parameterized Constructor
	FDamageData(float damage, EDamageRange range, EDamageTypes type)
	{
		damageVal = damage;
		damageRange = range;
		damageType = type;
	}

};
