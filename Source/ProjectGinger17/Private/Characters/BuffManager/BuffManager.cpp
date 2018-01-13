// Fill out your copyright notice in the Description page of Project Settings.

#include "BuffManager/BuffManager.h"


// Sets default values for this component's properties
UBuffManager::UBuffManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UBuffManager::BeginPlay()
{
	Super::BeginPlay();

	// If for whatever reason, the owner is not a valid character,
	// then there is no use for this component. Destroy it.
	if (!Cast<ABaseDotaCharacter>(GetOwner()))
	{
		MarkPendingKill();
		DestroyComponent();
	}
	
}


// Called every frame
void UBuffManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}


bool UBuffManager::AddBuff(UBaseBuff* buff) 
{ 
	if (activeBuffs.Contains(buff->buffName))
	{
		// Only insert additional entry to the list if the buff is stackable. Otherwise ignore the addition.
		if (buff->bStackable)
		{
			activeBuffs[buff->buffName].Insert(buff, 0);
			buff->BuffExpired().AddUObject(this, &UBuffManager::RemoveBuff); // Bind our function to the event
		}
		else
		{
			return false;
		}
	}
	else
	{
		// Create an associated List of Buff values and append our new Buff pointer.
		activeBuffs.Add(buff->buffName, TArray<UBaseBuff*>());
		activeBuffs[buff->buffName].Insert(buff, 0);
		buff->BuffExpired().AddUObject(this, &UBuffManager::RemoveBuff); // Bind our function to the event
	}

	buff->ApplyBuff(Cast<ABaseDotaCharacter>(GetOwner())->GetCharAttributes());
	return true;
}


bool UBuffManager::AddBuffByType(TAssetSubclassOf<UBaseBuff> buff)
{
	UBaseBuff* buffObj = NewObject<UBaseBuff>(this, buff.Get());

	if (buffObj)
	{
		return AddBuff(buffObj);
	}
	else
	{
		return false;
	}
}


void UBuffManager::RemoveBuff(FString buffName) 
{
	if (activeBuffs.Contains(buffName) && activeBuffs[buffName].Num() > 0)
	{
		// Since we are always inserting to index 0 of the List. The most outdated
		// buff will be the last one. Simply pop it.
		UBaseBuff* buffToRemove = activeBuffs[buffName].Pop();

		// DeApply the buff by passing the character attribute to modify once again (SUB-OPTIMAL)
		buffToRemove->DeApplyBuff(Cast<ABaseDotaCharacter>(GetOwner())->GetCharAttributes());

		// Mark as Pending Kill to safely remove all references to this object.
		// Set to NULL for Garbage Collector to destroy object.
		buffToRemove->MarkPendingKill();
		buffToRemove = NULL;

		// Invoke the blueprint event for debugging and extensibility.
		OnBuffRemoved.Broadcast();
	}
}

