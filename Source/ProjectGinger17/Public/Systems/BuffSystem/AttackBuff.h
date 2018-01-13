// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/BuffSystem/BaseBuff.h"
#include "HeroData/HeroAttackData.h"
#include "AttackBuff.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTGINGER17_API UAttackBuff : public UBaseBuff
{
	GENERATED_BODY()

public:
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attack Buff")
		FHeroAttackData attackBuffData;

		UAttackBuff();

		FORCEINLINE virtual void ApplyBuff(FDotaHeroAttributes* attributes) override;
		FORCEINLINE virtual void DeApplyBuff(FDotaHeroAttributes* attributes) override;
};
