// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Controllers/BaseDotaController.h"
//#include "Engine/World.h"
#include "ItemSystem/WorldItem.h"
#include "Characters/BaseDotaPlayer.h"
#include "ItemSystem/Interfaces/IPickup.h"
#include "ItemSystem/Interfaces/IInteractable.h"

ABaseDotaController::ABaseDotaController()
{
	gazeManager = CreateDefaultSubobject<UGazeManager>(TEXT("GazeManager"));

	gazeManager->OnFocusObjectChanged.AddUObject(this, &ABaseDotaController::FocusObjectChangedHandler);
	gazeManager->OnFocusObjectLost.AddUObject(this, &ABaseDotaController::FocusObjectLostHandler);
}

void ABaseDotaController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!GetPawn())
	{
		return;
	}

	// Verify if we are overlapping and looking at a specific object.
	if (gazeManager->FocusedObject() == overlappedActor && overlappedActor)
	{
		// Further verify if the item is something we can use or interact with
		if (Cast<IPickup>(overlappedActor))
		{
			DisplayNotification("Press E to Pickup");
			usableActor = overlappedActor;
		}
		else if (Cast<IInteractable>(overlappedActor))
		{
			DisplayNotification("Press E to Interact");
			usableActor = overlappedActor;
		}
		else
		{
			usableActor = NULL;
			ClearNotifications();
		}
	}
}

void ABaseDotaController::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hello from Dota Controller!"));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, GetPawn()->GetName());

	// Hooking the player's collision event to the controller. 
	// This has to be done on Begin Play as the construction script still did not POSSESS the pawn.
	if (Cast<ACharacter>(GetPawn()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Emerald, TEXT("Setting up collision events..."));
		GetPawn()->OnActorBeginOverlap.AddDynamic(this, &ABaseDotaController::OnBeginActorOverlap);
		GetPawn()->OnActorEndOverlap.AddDynamic(this, &ABaseDotaController::OnEndActorOverlap);
	}
}


void ABaseDotaController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Handle Movement, Strafe, and Turning. The choice of turning and strafing is handled
	// in the character's movement component.
	InputComponent->BindAxis("MoveForward", this, &ABaseDotaController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABaseDotaController::MoveRight);

	// Handle Mouse Movement
	InputComponent->BindAxis("Turn", this, &ABaseDotaController::Turn);
	InputComponent->BindAxis("LookUp", this, &ABaseDotaController::LookUp);

	// Handle Jumping
	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ABaseDotaController::Jump);
	InputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ABaseDotaController::StopJump);

	// Handle Basic Combat
	InputComponent->BindAction("AutoAttack", EInputEvent::IE_Pressed, this, &ABaseDotaController::AutoAttack);
	InputComponent->BindAction("AttackSpecial", EInputEvent::IE_Pressed, this, &ABaseDotaController::SpecialAttack);
	InputComponent->BindAction("AttackSpecial",EInputEvent::IE_Released, this, &ABaseDotaController::StopSpecialAttack);

	// Interactions
	InputComponent->BindAction("Use", EInputEvent::IE_Pressed, this, &ABaseDotaController::Use);

}

#pragma region INPUT_HANDLING

void ABaseDotaController::MoveForward(float scale)
{
	// Move the controlled char.
	if(Cast<ABaseDotaPlayer>(GetPawn()))
	{
		((ABaseDotaPlayer*)GetPawn())->MoveForward(scale);
	}
}


void ABaseDotaController::MoveRight(float scale)
{
	// Move the controlled char sideways or directionally depending on their current status
	if (Cast<ABaseDotaPlayer>(GetPawn()))
	{
		((ABaseDotaPlayer*)GetPawn())->MoveRight(scale);
	}
}


void ABaseDotaController::Turn(float scale)
{
	//FRotator newRotation = FRotator(0,  scale, 0);
	//SetControlRotation(GetControlRotation() + newRotation);
	AddYawInput(scale);
}

void ABaseDotaController::LookUp(float scale)
{
	//FRotator newRotation = FRotator(scale, 0, 0);
	//SetControlRotation(GetControlRotation() + newRotation);
	AddPitchInput(scale);
}

void ABaseDotaController::Jump()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("Pressing Jump"));
	if (Cast<ABaseDotaPlayer>(GetPawn()))
	{
		((ABaseDotaPlayer*)GetPawn())->Jump();
	}
}


void ABaseDotaController::StopJump()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("Released Jump"));
	if (Cast<ABaseDotaPlayer>(GetPawn()))
	{
		((ABaseDotaPlayer*)GetPawn())->StopJumping();
	}
}


void ABaseDotaController::AutoAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("Pressing Attack"));
	if (Cast<ABaseDotaPlayer>(GetPawn()))
	{

	}
}

void ABaseDotaController::StopAutoAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("Stopped Attack"));
}


void ABaseDotaController::SpecialAttack()
{
	if (Cast<ABaseDotaPlayer>(GetPawn()))
	{

	}
}

void ABaseDotaController::StopSpecialAttack()
{
	if (Cast<ABaseDotaPlayer>(GetPawn()))
	{

	}
}


void ABaseDotaController::Use()
{
	if(usableActor == NULL)
	{
		return;
	}

	/*OLD WEED
	if (usableActor->FindComponentByClass<UPickupItem>())
	{
		IPickup* pickup = Cast<IPickup>(usableActor->FindComponentByClass<UPickupItem>());

		if (pickup)
		{
			pickup->Execute_Pickup(usableActor->FindComponentByClass<UPickupItem>(), GetPawn());
		}
	}
	*/

	if (Cast<IPickup>(usableActor))
	{
		((IPickup*)usableActor)->Execute_Pickup(usableActor, GetPawn());
		usableActor = NULL;
	}
	else if (Cast<IInteractable>(usableActor))
	{
		((IInteractable*)usableActor)->Execute_Interact(usableActor, GetPawn());
		usableActor = NULL;
	}
}

#pragma endregion



#pragma region EVENT_HANDLERS
void ABaseDotaController::FocusObjectChangedHandler(FGazeEventData eventData)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("Focus Object Changed"));
}

void ABaseDotaController::FocusObjectLostHandler()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("Focus Object Lost"));
	ClearNotifications();
}

void ABaseDotaController::OnBeginActorOverlap(AActor* thisActor, AActor* otherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Overlapped Object"));
	overlappedActor = otherActor;
}

void ABaseDotaController::OnEndActorOverlap(AActor* thisActor, AActor* otherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Overlap Object Lost"));
	overlappedActor = NULL;
}
#pragma endregion