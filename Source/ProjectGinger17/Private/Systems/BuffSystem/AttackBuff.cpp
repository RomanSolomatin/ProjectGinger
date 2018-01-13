// Fill out your copyright notice in the Description page of Project Settings.

#include "BuffSystem/AttackBuff.h"

UAttackBuff::UAttackBuff()
{
	attackBuffData = FHeroAttackData();
}


FORCEINLINE void UAttackBuff::ApplyBuff(FDotaHeroAttributes* attributes) 
{
	Super::ApplyBuff(attributes);

	attributes->attackData.attackSpeed += attackBuffData.attackSpeed;
	attributes->attackData.baseDamage += attackBuffData.baseDamage;
	attributes->attackData.bonusDamage += attackBuffData.bonusDamage;
}


void UAttackBuff::DeApplyBuff(FDotaHeroAttributes* attributes)
{
	Super::DeApplyBuff(attributes);

	attributes->attackData.attackSpeed -= attackBuffData.attackSpeed;
	attributes->attackData.baseDamage -= attackBuffData.baseDamage;
	attributes->attackData.bonusDamage -= attackBuffData.bonusDamage;
}