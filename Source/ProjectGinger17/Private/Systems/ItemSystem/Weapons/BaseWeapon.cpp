// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "BuffSystem/BaseBuff.h"


// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	damageType = EWeaponDamageTypes::Normal;
	damage = 10;
	preAttkTime = 0.5f;
	postAttkTime = 0.2f;

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

}


bool ABaseWeapon::FireWeapon_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("FIRED WEAPON!"));
	return false;
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

UStaticMesh * ABaseWeapon::WeaponMesh()
{
	return weaponMesh->GetStaticMesh();
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
void ABaseWeapon::SetWeaponMesh(UStaticMesh * _mesh)
{
	weaponMesh->SetStaticMesh(_mesh);
}
#pragma endregion
