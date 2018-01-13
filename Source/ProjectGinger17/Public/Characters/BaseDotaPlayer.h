// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseDotaCharacter.h"
#include "BaseDotaPlayer.generated.h"

/**
 * Base Dota Player
 * Inherits all basic stat manipulation and events from the BaseDotaCharacter class.
 * Extends functionality by managing camera, movement input, and other player specific interfacing.
 */
UCLASS(BlueprintType)
class PROJECTGINGER17_API ABaseDotaPlayer : public ABaseDotaCharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Dota Player Properties")
	class UCameraComponent* playerCamera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Dota Player Properties")
	class USpringArmComponent* cameraBoom;

	
public:
	
	// Default Constructor
	ABaseDotaPlayer();


	// Fixates the character's rotation in the direction of its 
	// respective controller.
	UFUNCTION(BlueprintCallable, Category = "Dota Character Methods")
	void ResetCharacterRotation();

#pragma region MOVEMENT_HANDLING
	// Handles adding to the movement input vector until the movement speed is reached.
	virtual void MoveForward(float scalar);
	virtual void MoveRight(float scalar);

	FORCEINLINE virtual void Turn(FRotator toRotation);
#pragma endregion
	
	
};
