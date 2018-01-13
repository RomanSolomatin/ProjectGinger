// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseItemInfo.h"
#include "GameFramework/Actor.h"
#include "Inventory/InventorySlot.h"
#include "BaseGameItem.generated.h"

UCLASS(Abstract)
class PROJECTGINGER17_API ABaseGameItem : public AActor
{
	GENERATED_BODY()
		
/// <Summary>
/// Inherited Functions
/// </Summary>
public:	
	// Sets default values for this actor's properties
	ABaseGameItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Base Item Properties")
	FBaseItemInfo itemInfo;

public:

	/// Accessor Functions
	FName GetItemRowName();
	FString GetItemName();
	FString GetItemDescription();
	const FBaseItemInfo GetBaseItemInfo();
	

	/// Mutator Functions
	void SetItemRowName(FName _name);
	void SetItemName(FString _name);
	void SetItemDescription(FString _description);
};
