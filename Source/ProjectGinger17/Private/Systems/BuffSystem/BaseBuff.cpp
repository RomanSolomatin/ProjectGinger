// Fill out your copyright notice in the Description page of Project Settings.

#include "BuffSystem/BaseBuff.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Default Constructor
UBaseBuff::UBaseBuff()
{
	buffName = TEXT("DefaultBuff");
	bExpires = false;
	buffDuration = 1;
}

UBaseBuff::UBaseBuff(FString _buffName)
{
	buffName = _buffName;
	bExpires = false;
	buffDuration = 1;
}

void UBaseBuff::BuffExpiredHandler()
{
	GetOuter()->GetWorld()->GetTimerManager().ClearTimer(expiryTimerHandler);
	BuffExpiredEvent.Broadcast(buffName);

	// Call the Blueprint Event to introduce blueprint functionalities down the line.
	OnBuffExpired();
}

// If the Buff has a duration, activate it and start its timer.
void UBaseBuff::ActivateBuff()
{
	if (bExpires && !expiryTimerHandler.IsValid() && buffDuration > 0)
	{
		GetOuter()->GetWorld()->GetTimerManager().SetTimer(expiryTimerHandler, this, &UBaseBuff::BuffExpiredHandler, buffDuration, false );
	}

	// Do Stuff
}


void UBaseBuff::ResetBuffDuration()
{
	if (expiryTimerHandler.IsValid())
	{
		GetOuter()->GetWorld()->GetTimerManager().SetTimer(expiryTimerHandler, this, &UBaseBuff::BuffExpiredHandler, buffDuration, false);

		// Optional : Resume the timer if paused.
		if (GetOuter()->GetWorld()->GetTimerManager().IsTimerPaused(expiryTimerHandler))
		{
			GetOuter()->GetWorld()->GetTimerManager().UnPauseTimer(expiryTimerHandler);
		}
		
	}
}


void UBaseBuff::TogglePause()
{
	if(!expiryTimerHandler.IsValid())
	{ return; }

	// If the timer is paused, then unpause it.
	if (GetOuter()->GetWorld()->GetTimerManager().IsTimerPaused(expiryTimerHandler))
	{
		GetOuter()->GetWorld()->GetTimerManager().PauseTimer(expiryTimerHandler);
	}
	// Otherwise simply pause it
	else
	{
		GetOuter()->GetWorld()->GetTimerManager().UnPauseTimer(expiryTimerHandler);
	}
}

// Overriden in derived classes. Applies stats modification
// to the provided attributes and activates the buff timer.
void UBaseBuff::ApplyBuff(FDotaHeroAttributes* attributes)
{
	if (!attributes) { return; }
	ActivateBuff();
}

// Overriden in the derived classes. Removes the stats modification
// to the provided attributes.
void UBaseBuff::DeApplyBuff(FDotaHeroAttributes* attributes)
{
	if (!attributes) { return; }
}