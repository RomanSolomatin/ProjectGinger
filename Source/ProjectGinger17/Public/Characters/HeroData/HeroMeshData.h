// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HeroMeshData.generated.h"

UENUM(BlueprintType)
enum class EMeshLayoutSlots : uint8
{ Head = 0, Torso, Shoulders, Arms, Legs};

/**
 * Hero Mesh Data
 * Contains the visual layout of the hero's
 * mesh composition. Contains definition of the base
 * hero model as well as attachable cosmetic meshes.
 */
USTRUCT(BlueprintType)
struct FHeroMeshData
{
	GENERATED_BODY()
public:
	FHeroMeshData() {}

	// Holds a list of attachable cosmetic items on the hero based on their
	// slot location (head, arms, legs etc).
	/*
	/* @Slot1 = Head
	/* @Slot2 = Torso
	/* @Slot3 = Shoulders
	/* @Slot4 = Arms
	/* @Slot5 = Legs
	*/

protected:

	// An Array to contain the 5 cosmetic item slots.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Mesh Data")
	TArray<class USkeletalMesh*> cosmeticMeshes = { NULL, NULL, NULL, NULL, NULL };

	// Base Model of the hero. Cannot be modified in game.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hero Mesh Data")
	class USkeletalMesh* baseMesh = NULL;

#pragma region STRUCT_METHODS
public:

	// Sets the specified slot using the specified mesh.
	void SetMeshSlot(USkeletalMesh* mesh, EMeshLayoutSlots slot)
	{
		if ((uint8)slot >= 0 && (uint8)slot <= cosmeticMeshes.Num())
		{
			cosmeticMeshes[(uint8)slot] = mesh;
		}
	}

	// Clears all the attached cosmetic meshes from the Hero.
	void ClearMeshes()
	{
		for (USkeletalMesh* mesh : cosmeticMeshes)
		{
			mesh = NULL;
		}
	}


#pragma endregion

};
