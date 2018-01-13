// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/BaseDotaPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Default Constructor
ABaseDotaPlayer::ABaseDotaPlayer()
{
	// Component Initializations
	playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));

	// Attachment Setup
	cameraBoom->SetupAttachment(RootComponent);
	playerCamera->SetupAttachment(cameraBoom);

	// Component Values
	cameraBoom->SocketOffset = FVector(0, 0, 0);
	cameraBoom->bUsePawnControlRotation = true;
	cameraBoom->bInheritPitch = cameraBoom->bInheritRoll = cameraBoom->bInheritYaw = true;

}


void ABaseDotaPlayer::ResetCharacterRotation()
{
	Turn(GetControlRotation());
}


/* Input handling and responses. Drives character locomotion and responses to key presses */
#pragma region MOVEMENT_HANDLING
void ABaseDotaPlayer::MoveForward(float scalar)
{
	// If the character is set to strafe, simply translate back and forth without turning.
	if (bStrafe)
	{
		Turn(GetControlRotation());
		AddMovementInput(GetController()->GetActorForwardVector(), 5.0f * scalar, false);
	}
	else
	{
		AddMovementInput(GetController()->GetActorForwardVector(), 5.0f * scalar, false);
	}

}

void ABaseDotaPlayer::MoveRight(float scalar)
{
	// If the character is set to strafe mode, simply translate sideways.
	if (bStrafe)
	{
		Turn(GetControlRotation());
		AddMovementInput(GetController()->GetActorRightVector(), 5.0f * scalar, false);
	}
	// Otherwise, Turn the player towards the direction vector first, then move.
	else
	{
		AddMovementInput(GetController()->GetActorRightVector(), 5.0f * scalar, false);
	}

}

// Turn the player to face a specific rotation smoothly.
void ABaseDotaPlayer::Turn(FRotator toRotation)
{
	FRotator targetRot = FRotator(0, toRotation.Yaw, 0);
	SetActorRotation(FMath::Lerp(GetActorRotation(), targetRot, 0.1f));
}
#pragma endregion