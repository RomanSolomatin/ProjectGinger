// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GazeManager/GazeEventData.h"
#include "GazeManager.generated.h"

/*	Gaze Manager
* The Gaze Manager is a component attached to player controllers.
* It is responsible for probing the player's surrounding and sends
* feedback to the player controller regarding which object is currently being
* looked at. It also uses several events the controller subscribes to in case
* the focus object changes.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTGINGER17_API UGazeManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGazeManager();

	DECLARE_EVENT_OneParam(UGazeManager, FFocusObjectChanged, FGazeEventData);
	FFocusObjectChanged OnFocusObjectChanged;

	DECLARE_EVENT(UGazeManager, FFocusObjectLost);
	FFocusObjectLost OnFocusObjectLost;


protected:

	// Blueprint Variant of FocusedObject. Use INLINE version inside C++ for optimal performance.
	// Returns the object that is currently being looked at by the player.
	// Returns NULL if nothing was found.
	UFUNCTION(BlueprintCallable, Category = "Gaze Manager Methods")
	AActor* GetFocusedObject();

private:
	/* Gaze Manager Variables */

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gaze Manager Properties", meta=(AllowPrivateAccess = "true"))
	float traceDistance = 100.f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gaze Manager Properties", meta = (AllowPrivateAccess = "true"))
	float traceRadius = 25.f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gaze Manager Properties", meta = (AllowPrivateAccess = "true"))
	bool debugDraw;

	UPROPERTY(BlueprintReadOnly, Category = "Gaze Manager Properties", meta = (AllowPrivateAccess = "true"))
	AActor* currGazedObject;

	UPROPERTY(BlueprintReadOnly, Category = "Gaze Manager Properties", meta = (AllowPrivateAccess = "true"))
	AActor* referenceActor;

	FCollisionQueryParams traceParams;
	FGazeEventData eventData;

public:	
	// Use Spherical Tracing to detect objects being looked at.
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;

	// Returns the object that is currently being looked at by the player.
	// Returns NULL if nothing was found.
	FORCEINLINE AActor* FocusedObject();
};