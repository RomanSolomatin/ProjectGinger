// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Characters/BaseDotaCharacter.h"
#include "BaseBuff.generated.h"

/**
 * Base Buff Object
 * Defines an abstract buff object that can be managed
 * by the character's Buff Manager. 
 * @Params
 * @ int Id - Unique identifier. Each buff is a unique effect and cannot be stacked.
 * @ bool bExpirs - Determines if the buff is timed. Changing this value during runtime
					will fire an event that will pause or resume existing timers.
 * @ int buffDuration - The time in seconds this buff will last.
 */
UCLASS(Abstract, BlueprintType)
class PROJECTGINGER17_API UBaseBuff : public UObject
{
	GENERATED_BODY()

	// Declare an event signature that the buff object will dispatch.
	// FBuffExpired(int32)
	// Where int32 is the Id of the expiring buff.
	DECLARE_EVENT_OneParam(UBaseBuff, FBuffExpired, FString)

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Buff Properties")
	FString buffName;

	// Determines whether this buff can expire using a timer. Otherwise, it is
	// applied permanently and passively until the buff is forcefully removed.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Buff Properties")
	bool bExpires;

	// The duration of this buff assuming its set to expire.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Buff Properties")
	int32 buffDuration;

	// Indicates whether multiple instances of this buff can exist.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Buff Properties")
	bool bStackable;

	// Public Accessor for event
	FBuffExpired& BuffExpired()
	{
		return BuffExpiredEvent;
	}



	// Default Constructor
	UBaseBuff();

	UBaseBuff(FString _buffName);

	// Activates the Buff by setting a timer for its duration. Invoke the
	// BuffExpired event when the timer elapses.
	void ActivateBuff();

	// Resets the timer on a currently active buff.
	void ResetBuffDuration();

	// Pure Virtual. Each type of buff manipulates the hero attributes in a different manner.
	FORCEINLINE virtual void ApplyBuff(FDotaHeroAttributes* attributes);

	FORCEINLINE virtual void DeApplyBuff(FDotaHeroAttributes* attributes);

	UFUNCTION(BlueprintCallable, Category = "Base Buff Methods")
	void TogglePause();

	// Blueprint Event - Invoked internally when the duration of the buff expires.
	UFUNCTION(BlueprintImplementableEvent, Category = "Base Buff Events")
	void OnBuffExpired();

protected:

	// The Event to be invoked when the buff timer runs out.
	FBuffExpired BuffExpiredEvent;

	// A placeholder Timer Handler. Use to reference an existing timer.
	// Helps manipulate a set timer (i.e pause, clear, etc).
	FTimerHandle expiryTimerHandler;
	
	// Overridable event invoking function. Used to modify event invokation
	// in derived classes.
	virtual void BuffExpiredHandler();
	
};
