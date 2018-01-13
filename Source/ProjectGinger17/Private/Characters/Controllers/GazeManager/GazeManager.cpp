// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/GazeManager/GazeManager.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "ItemSystem/Interfaces/IPickup.h"
#include "ItemSystem/Interfaces/IInteractable.h"


// Sets default values for this component's properties
UGazeManager::UGazeManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}


void UGazeManager::BeginPlay()
{
	Super::BeginPlay();

	// If the Gaze Manager is attached to a Player Controller,
	// we need a reference to the pawn being controlled.
	if (Cast<APlayerController>(GetOwner()))
	{
		referenceActor = ((AActor*)((APlayerController*)GetOwner())->GetPawn());
	}

	// Otherwise, directly use our owner as a reference.
	else
	{
		referenceActor = GetOwner();
	}

	traceParams = FCollisionQueryParams(FName(TEXT("TraceParams")), false, referenceActor);
}


// Called every frame
void UGazeManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// In case for whatever reason, the component was not attached to a proper Actor.
	if (!referenceActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("GazeManager: No Actor reference found. Code cannot be executed without a proper owning Actor."))
		return;
	}

	FHitResult hitInfo = FHitResult(EForceInit::ForceInit);

	bool hitSuccess = GetWorld()->SweepSingleByObjectType(hitInfo, referenceActor->GetActorLocation(), referenceActor->GetActorLocation() + referenceActor->GetActorForwardVector() * traceDistance, FQuat::Identity, FCollisionObjectQueryParams::AllObjects, FCollisionShape::MakeSphere(traceRadius), traceParams);

	// Draw the shapes for debugging purposes
	if (debugDraw)
	{
		DrawDebugLine(
			GetWorld(),
			referenceActor->GetActorLocation(),
			referenceActor->GetActorLocation() + referenceActor->GetActorForwardVector() * traceDistance,
			FColor(255, 0, 0),
			false, -1, 0,
			12.333
		);

		DrawDebugSphere(GetWorld(), referenceActor->GetActorLocation(), traceRadius, 12, FColor::Red, false, -1, 0, 5);
	}

	// If the sweep successfully hits an Actor, update our event struct select the event to invoke.
	if (hitSuccess)
	{
		// Overwrite our previous focus actor since we detected a new one.
		eventData.PreviousFocusActor = currGazedObject;

		if (hitInfo.GetActor())
		{	
			if (hitInfo.GetActor() == currGazedObject)
			{
				return;
			}

			// Set the current gaze object as the FocusedActor.
			currGazedObject = hitInfo.GetActor();
			eventData.FocusedActor = currGazedObject;

			Cast<IPickup>(currGazedObject) != NULL ? eventData.bIsPickup = true : eventData.bIsPickup = false;
			Cast<IInteractable>(currGazedObject) != NULL ? eventData.bIsInteract = true : eventData.bIsInteract = false;

			OnFocusObjectChanged.Broadcast(eventData);
		}

		// If the hit was successful but for some reason an Actor was not found. Safely
		// Default to a NULL value and invoke a Focus Lost event.
		else
		{
			currGazedObject = NULL;
			eventData.FocusedActor = currGazedObject;

			OnFocusObjectLost.Broadcast();
		}
	}

	// Lost focus of any object
	else
	{
		if (currGazedObject != NULL)
		{
			currGazedObject = NULL;
			OnFocusObjectLost.Broadcast();
		}
	}
}

AActor * UGazeManager::GetFocusedObject()
{
	return currGazedObject;
}

AActor * UGazeManager::FocusedObject()
{
	return currGazedObject;
}
