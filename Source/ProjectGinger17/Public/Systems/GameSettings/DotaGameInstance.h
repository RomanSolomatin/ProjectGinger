// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/GameInstance.h"
#include "ItemSystem/Factory/ItemFactory.h"
#include "DotaGameInstance.generated.h"

/** Dota Game Instance : UGameInstance
 * A High level persistent class derived from GameInstance.
 * Maintains globally accessed Singleton classes such as Factory and Manager classes.
 */
UCLASS()
class PROJECTGINGER17_API UDotaGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UDotaGameInstance(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Dota Game Instance")
	AItemFactory* ItemFactory;	
};
