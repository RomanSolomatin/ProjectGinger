// Fill out your copyright notice in the Description page of Project Settings.

#include "BuffSystem/StatsBuff.h"


UStatsBuff::UStatsBuff()
{
	statsBuffData = FHeroStatsData();
}

FORCEINLINE void UStatsBuff::ApplyBuff(FDotaHeroAttributes* attributes)
{
	Super::ApplyBuff(attributes);

	attributes->statsData.armor += statsBuffData.armor;
	attributes->statsData.healthPool += statsBuffData.healthPool;
	attributes->statsData.manaPool += statsBuffData.manaPool;
	attributes->statsData.magicResistance += statsBuffData.magicResistance;
	attributes->statsData.moveSpeed += statsBuffData.moveSpeed;
}

void UStatsBuff::DeApplyBuff(FDotaHeroAttributes* attributes)
{
	Super::DeApplyBuff(attributes);

	attributes->statsData.armor -= statsBuffData.armor;
	attributes->statsData.healthPool -= statsBuffData.healthPool;
	attributes->statsData.manaPool -= statsBuffData.manaPool;
	attributes->statsData.magicResistance -= statsBuffData.magicResistance;
	attributes->statsData.moveSpeed -= statsBuffData.moveSpeed;
}