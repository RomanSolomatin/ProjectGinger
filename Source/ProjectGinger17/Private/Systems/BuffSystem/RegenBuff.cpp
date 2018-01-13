// Fill out your copyright notice in the Description page of Project Settings.

#include "BuffSystem/RegenBuff.h"


URegenBuff::URegenBuff()
{
	regenBuffData = FHeroRegenData();
}

FORCEINLINE void URegenBuff::ApplyBuff(FDotaHeroAttributes* attributes)
{
	Super::ApplyBuff(attributes);

	attributes->regenData.healthRegen += regenBuffData.healthRegen;
	attributes->regenData.manaRegen += regenBuffData.manaRegen;
}

void URegenBuff::DeApplyBuff(FDotaHeroAttributes* attributes)
{
	Super::DeApplyBuff(attributes);

	attributes->regenData.healthRegen -= regenBuffData.healthRegen;
	attributes->regenData.manaRegen -= regenBuffData.manaRegen;
}