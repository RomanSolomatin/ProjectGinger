// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/GameSettings/DotaGameInstance.h"

UDotaGameInstance::UDotaGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	if (!ItemFactory)
	{
		ItemFactory = NewObject<AItemFactory>();
	}
}


