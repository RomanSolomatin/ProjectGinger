// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSystem/BaseGameItem.h"
#include "ItemSystem/Interfaces/IWeapons.h"
#include "ItemSystem/Interfaces/IEquippable.h"
#include "BaseWeapon.generated.h"


/*	Weapon Damage Types
*	These flags determine the category of damage the weapon applies.
*	The damage calculation function takes this into account to output
*	scaled damage values depending on the target's class.
*
*	Normal:		Default damage calculation. Include the target's armor (if applicable) to modify the final damage value.
*	Pierce:		Damage calculation ignores ONLY armor values of creatures -- effectively piercing through it. Conversely, damage is heavily reduced against structures.
*	Pure:		Damage calculation ignores all factors and subtracts health using the raw damage value of the weapon.
*	Seige:		Damage calculation ignores ONLY armor values of structures. Conversely, damage is heavily reduced against creatures.
*/
UENUM(BlueprintType)
enum class EWeaponDamageTypes : uint8
{
	Normal, Pierce, Pure, Seige
};


/* Base Weapon Actor
*	This class represents a base for all weapon actors that can be spawned
*	and attached as part of the equipment process.
*/
UCLASS(Abstract)
class PROJECTGINGER17_API ABaseWeapon : public ABaseGameItem, public IIWeapons, public IEquippable
{
	GENERATED_BODY()

protected:

#pragma region WEAPON_FIRE_PROPERTIES

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Firing Properties")
		float damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Firing Properties")
		EWeaponDamageTypes damageType;

	/*	Also Backswing Time
	*
	*	This is the time the weapon takes to swing back and charge before launching an attack.
	*	This quantity is used by the character's animation system to control the playback speed
	*	of the backswing animation.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Firing Properties")
		float preAttkTime;

	/*
	*	This is the time the weapon takes to swing and attack.
	*	This quantity is used by the character's animation system to control the playback speed
	*	of the attack swing animation.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Firing Properties")
		float postAttkTime;

#pragma endregion

#pragma region WEAPON_ANIMATION_FLAGS
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Animation Properties")
		bool bDetectHits;

#pragma endregion




protected:

#pragma region WEAPON_BASIC_PROPERTIES

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Weapon Visual")
	class USkeletalMeshComponent* weaponMesh;

	/*	Modifier List
	*
	*	Contains a list of buff/debuffs the weapon will apply
	*	on each hit.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Modifiers")
	TArray<TAssetSubclassOf<class UBaseBuff>> weaponModifiers;

#pragma endregion



	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Issues a firing command to the weapon. Effectively launching the attack sequence
	// for either Melee or Ranged weapons. Melee weapons will depend on their associated collision mesh
	// to apply damage, whereas ranged weapons will simply launch the projectile.
	virtual bool FireWeapon_Implementation() override;
	virtual void OnEquipped_Implementation() override;
	virtual void OnDeEquipped_Implementation() override;

	
#pragma region GETTERS_SETTERS
	float Damage();
	float PreAttackTime();
	float PostAttackTime();
	
	EWeaponDamageTypes DamageType();
	class USkeletalMesh* WeaponMesh();
	TArray<TAssetSubclassOf<class UBaseBuff>> &GetWeaponModifiers();


	void SetDamage(float _damage);
	void SetPreAttackTime(float _preAttkTime);
	void SetPostAttackTime(float _postAttkTime);

	void SetWeaponMesh(class USkeletalMesh* _mesh);
	void SetWeaponModifiers(TArray<TAssetSubclassOf<class UBaseBuff>> _modifiers);
	void SetWeaponDamageType(EWeaponDamageTypes _damageType);
#pragma endregion
};
