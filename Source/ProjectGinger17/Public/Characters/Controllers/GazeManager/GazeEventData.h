// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

/**
 * Gaze Event Data
 * Holds information to be passed by events within the
 * Gaze Management Component.
 */

/*
class PROJECTGINGER17_API GazeEventData
{
public:
	GazeEventData();
	~GazeEventData();
};
*/

struct FGazeEventData
{
public:
	AActor* FocusedActor;
	AActor* PreviousFocusActor;

	bool bIsPickup;
	bool bIsInteract;

	FGazeEventData()
	{
		FocusedActor = NULL;
		PreviousFocusActor = NULL;

		bIsPickup = bIsInteract = false;
	}

};