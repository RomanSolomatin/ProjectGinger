// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/ItemSystem/WorldItem.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Systems/GameSettings/DotaGameInstance.h"
#include "Components/StaticMeshComponent.h"


#pragma region Editor Functions

// Constructor for this class
AWorldItem::AWorldItem()
{
	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Set the base Scene Component as a root with to hold our Transforms.
	RootComponent = root;

	// Append Remaining components
	collisionBox->SetupAttachment(root);
	itemMesh->SetupAttachment(RootComponent); 
	InitWorldItem();
}

void AWorldItem::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("Item Property Changed: Updating..."));

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *PropertyChangedEvent.GetPropertyName().ToString());
}

#pragma endregion

// Accessor Functions
#pragma region Getters

UStaticMeshComponent* AWorldItem::GetItemMesh()
{
	return itemMesh;
}

UBoxComponent* AWorldItem::GetItemCollisionBox()
{
	return collisionBox;
}

UBoxComponent* AWorldItem::GetItemInteractBox()
{
	return interactBox;
}

EItemMaterials AWorldItem::GetItemMaterial()
{
	return itemMaterial;
}

UAudioComponent* AWorldItem::GetItemAudio()
{
	return itemAudio;
}

UParticleSystemComponent*  AWorldItem::GetItemParticleSystem()
{
	return itemParticles;
}

#pragma endregion

#pragma region Setters
void AWorldItem::SetItemMesh(UStaticMesh* _staticMesh)
{
	itemMesh->SetStaticMesh(_staticMesh);
}

void AWorldItem::SetItemCollisionBox(FVector _collisionBox)
{
	collisionBox->SetBoxExtent(_collisionBox, true);
}

void AWorldItem::SetItemInteractBox(FVector _interactBox)
{
	interactBox->SetBoxExtent(_interactBox, true);
}

void AWorldItem::SetItemMaterial(EItemMaterials _material)
{
	itemMaterial = _material;
}

#pragma endregion


#pragma region NATIVE METHODS


#pragma endregion

// Use the DataTable to initialize values of this class.
void AWorldItem::InitWorldItem()
{
	// Set Mesh and Collision Box properties
}

// Function that handles Item's death.
// If DeathByDamage is true, the item was killed by a damage source,
// execute destruction sequence. Otherwise, the item was despawned due to
// generic causes - i.e, Picked up.
void AWorldItem::RemoveItem()
{
	Destroy();
}
