// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/ItemSystem/Structures/BaseStructureItems.h"
#include "ItemSystem/Interfaces/IInteractable.h"
#include "Door.generated.h"

UENUM(BlueprintType)
enum class EDoorTypes : uint8
{ Rotating, Sliding };

/**
 * 
 */
UCLASS()
class PROJECTGINGER17_API ADoor : public ABaseStructureItems // public IInteractable
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Door Properties")
	EDoorTypes doorType;

private:

	/* These internal variables are used to manage the behaviour of the door via the use of states and flags */
	
	bool bIsOpen;
	bool bStartsOpen;
	

	
	
};
