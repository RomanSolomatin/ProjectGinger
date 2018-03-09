// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/ItemSystem/Weapons/BaseWeapon.h"
#include "BaseMeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGINGER17_API ABaseMeleeWeapon : public ABaseWeapon
{
	GENERATED_BODY()
	
public:

	virtual bool FireWeapon_Implementation() override;
	
	
};
