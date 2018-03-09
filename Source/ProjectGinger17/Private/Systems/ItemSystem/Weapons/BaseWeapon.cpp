// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "BuffSystem/BaseBuff.h"


// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	damageType = EWeaponDamageTypes::Normal;
	damage = 10;
	preAttkTime = 0.5f;
	postAttkTime = 0.2f;

	bDetectHits = false;

	weaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = weaponMesh;
	weaponModifiers.Reserve(1);

	SetActorEnableCollision(false);

}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// To avoid unecessary caches of the memory, allow the actor
	// to destroy itself if it has not been used recently.
	if (!WasRecentlyRendered())
	{
		Destroy();
	}
}


// Interfaces

bool ABaseWeapon::FireWeapon_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("FIRED WEAPON!"));
	return false;
}

void ABaseWeapon::OnEquipped_Implementation()
{
}

void ABaseWeapon::OnDeEquipped_Implementation()
{
}




#pragma region GETTERS_SETTERS
float ABaseWeapon::Damage()
{
	return damage;
}

float ABaseWeapon::PreAttackTime()
{
	return preAttkTime;
}

float ABaseWeapon::PostAttackTime()
{
	return postAttkTime;
}

EWeaponDamageTypes ABaseWeapon::DamageType()
{
	return damageType;
}

USkeletalMesh* ABaseWeapon::WeaponMesh()
{
	return weaponMesh->SkeletalMesh;
}

TArray<TAssetSubclassOf<UBaseBuff>> &ABaseWeapon::GetWeaponModifiers()
{
	return weaponModifiers;
}



void ABaseWeapon::SetDamage(float _damage)
{
	damage = _damage;
}

void ABaseWeapon::SetPreAttackTime(float _preAttkTime)
{
	preAttkTime = _preAttkTime;
}

void ABaseWeapon::SetPostAttackTime(float _postAttkTime)
{
	postAttkTime = _postAttkTime;
}
void ABaseWeapon::SetWeaponMesh(USkeletalMesh* _mesh)
{
	weaponMesh->SetSkeletalMesh(_mesh);
}
void ABaseWeapon::SetWeaponModifiers(TArray<TAssetSubclassOf<class UBaseBuff>> _modifiers)
{
	weaponModifiers = _modifiers;
}
void ABaseWeapon::SetWeaponDamageType(EWeaponDamageTypes _damageType)
{
	damageType = _damageType;
}
#pragma endregion
