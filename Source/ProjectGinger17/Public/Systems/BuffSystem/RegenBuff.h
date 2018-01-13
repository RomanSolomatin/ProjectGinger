// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/BuffSystem/BaseBuff.h"
#include "HeroData/HeroRegenData.h"
#include "RegenBuff.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTGINGER17_API URegenBuff : public UBaseBuff
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Regen Buff")
	FHeroRegenData regenBuffData;
	
	URegenBuff();

	FORCEINLINE virtual void ApplyBuff(FDotaHeroAttributes* attributes) override;
	FORCEINLINE virtual void DeApplyBuff(FDotaHeroAttributes* attributes) override;
};
