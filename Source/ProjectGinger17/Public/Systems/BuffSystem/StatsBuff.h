// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/BuffSystem/BaseBuff.h"
#include "HeroData/HeroStatsData.h"
#include "StatsBuff.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTGINGER17_API UStatsBuff : public UBaseBuff
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats Buff")
	FHeroStatsData statsBuffData;
	

	UStatsBuff();
	

	FORCEINLINE virtual void ApplyBuff(FDotaHeroAttributes* attributes) override;
	FORCEINLINE virtual void DeApplyBuff(FDotaHeroAttributes* attributes) override;
};
