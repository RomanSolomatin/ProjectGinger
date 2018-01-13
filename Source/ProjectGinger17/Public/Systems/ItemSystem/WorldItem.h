// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/ItemSystem/BaseGameItem.h"
#include "Engine/World.h"
#include "WorldItem.generated.h"

UENUM(BlueprintType)
enum class EItemMaterials:uint8
{
	M_Wood,
	M_Metal,
	M_Ceramic,
	M_Glass,
	M_Dirt,
	M_Grass,
	M_Concrete,
	M_Plastic
};

/**
 * 
 */
UCLASS(Abstract)
class PROJECTGINGER17_API AWorldItem : public ABaseGameItem
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "World Item Properties")
		USceneComponent* root;

	// Defines a Static Mesh component for the item.
	UPROPERTY(VisibleAnywhere, Category = "World Item Properties")
		class UStaticMeshComponent* itemMesh;

	UPROPERTY(VisibleAnywhere, Category = "World Item Properties")
		class UParticleSystemComponent* itemParticles;

	UPROPERTY(VisibleAnywhere, Category = "World Item Properties")
		class UAudioComponent* itemAudio;

	// Defines a Shape Component, representing the collision box of the item.
	UPROPERTY(VisibleAnywhere, Category = "World Item Properties")
		class UBoxComponent* collisionBox;

	// Defines a physical material that will be used to render decals and sounds.
	UPROPERTY(VisibleAnywhere, Category = "World Item Properties")
		EItemMaterials itemMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "World Item Properties")
		UBoxComponent* interactBox;
	
public:
	// Constructor for this class
	AWorldItem();

	// Updates the item as soon as a property is changed in the editor.
	void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;
	
#pragma region Getters

	UStaticMeshComponent* GetItemMesh();

	UBoxComponent* GetItemCollisionBox();

	UBoxComponent* GetItemInteractBox();

	UAudioComponent* GetItemAudio();

	UParticleSystemComponent* GetItemParticleSystem();

	EItemMaterials GetItemMaterial();

#pragma endregion


#pragma region Setters
	UFUNCTION(BlueprintCallable, Category = "World Item - DEBUG")
	void SetItemMesh(UStaticMesh* _staticMesh);
	
	void SetItemCollisionBox(FVector _collisionBox);

	void SetItemInteractBox(FVector _interactBox);

	void SetItemMaterial(EItemMaterials _material);
#pragma endregion

#pragma region NATIVE METHODS



#pragma endregion


	// Handle Despawning this item due to non damage sources (i.e Pickup)
	UFUNCTION(BlueprintCallable, Category = "World Item")
	void RemoveItem();


private:
	// Use the DataTable to initialize values of this class.
	void InitWorldItem();
};
