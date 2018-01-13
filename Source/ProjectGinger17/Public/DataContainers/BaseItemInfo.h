// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BaseItemInfo.generated.h"

/*
/* BaseItemInfo
/* A structure that holds the most basic item information
/* shared by all item classes.
/* @param FName ItemRowName: The ID used to search the Item Database
/* @param FString ItemName: In game display name of the item
/* @param FString Description: In game display description of the item
*/
USTRUCT(BlueprintType)
struct FBaseItemInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Base Item Properties")
		FName itemRowName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Base Item Properties")
		FString itemName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Base Item Properties")
		FString itemDescription;

	FBaseItemInfo(FName row, FString name, FString description)
	{
		itemRowName = row;
		itemName = name;
		itemDescription = description;
	}

	FBaseItemInfo()
	{
		itemRowName = FName(TEXT(""));
		itemName = FString(TEXT(""));
		itemDescription = FString(TEXT(""));
	}
};
