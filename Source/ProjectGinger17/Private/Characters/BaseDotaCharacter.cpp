// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/BaseDotaCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BuffManager/BuffManager.h"
#include "Inventory/BaseInventory.h"
#include "TimerManager.h"
#include "Engine/StaticMesh.h"

/* Includes fundmanetal gameplay and construction event */
#pragma region INITIALIZATIONS


// Sets default values
ABaseDotaCharacter::ABaseDotaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	socketMap.Add(0, equipSlot_L);
	socketMap.Add(1, equipSlot_R);
	socketMap.Add(2, NULL);

	// Base Dota Character Default Variables
	characterState = ECharacterStates::Neutral;
	bStrafe = false;
	turnRate = FRotator(0, 360, 0);

	// Character Default Variables
	JumpMaxHoldTime = 0.1;
	JumpMaxCount = 2;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	// Component Initialization
	buffManager = CreateDefaultSubobject<UBuffManager>(TEXT("BuffManager"));
	inventory = CreateDefaultSubobject<UBaseInventory>(TEXT("Inventory"));
	equipSlot_L = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LEquipMesh"));
	equipSlot_R = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("REquipMesh"));

	// Attachment Setup
	equipSlot_L->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName(TEXT("S_LHand")));
	equipSlot_R->SetupAttachment(GetMesh(), FName(TEXT("S_RHand")));

	socketMap.Add(0, equipSlot_L);
	socketMap.Add(1, equipSlot_R);
	socketMap.Add(2, NULL);
	
	// Event Subscription
	StatsUpdated.AddDynamic(this, &ABaseDotaCharacter::OnStatsUpdated);
	OnCharacterStateChanged.AddUFunction<ABaseDotaCharacter>(this, FName(TEXT("CharacterStateChangedHandler")));
}


// Called when the game starts or when spawned
void ABaseDotaCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	currHealth = attributes.statsData.healthPool;
	currMana = attributes.statsData.manaPool;

	// Handle Post Construction Initialization
	ReInitializeChar();

	GetWorld()->GetTimerManager().SetTimer(updateTimerHandler, this, &ABaseDotaCharacter::UpdateStats, 1, true);
}

// Called every frame
void ABaseDotaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#pragma endregion


/* Higher Level Character specific funtionalities*/
#pragma region DOTA_CHAR_METHODS

void ABaseDotaCharacter::UpdateStats()
{
	currHealth = FMath::Clamp(currHealth + attributes.regenData.healthRegen, 0.f, attributes.statsData.healthPool);
	currMana = FMath::Clamp(currMana + attributes.regenData.manaRegen, 0.f, attributes.statsData.manaPool);

	// Tell all other listeners we updated the character
	StatsUpdated.Broadcast();
}


void ABaseDotaCharacter::SetEquipSlot(int socketId, UStaticMesh* _mesh)
{
	if (!_mesh)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Provided mesh is NULL!"));
	}
	if (socketMap.Contains(socketId))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Found STATIC MESH COMPONENT!"));
		if(socketMap[socketId] != NULL)
		socketMap[socketId]->SetStaticMesh(_mesh);
	}
}


// Debug Method to toggle the character's strafe.
void ABaseDotaCharacter::ToggleStrafe()
{
	bStrafe = !bStrafe;
	GetCharacterMovement()->bOrientRotationToMovement = !bStrafe;
}

#pragma endregion

// Allows components and other classes to modify the state of the character.
// Invokes the OnCharacterStateChanged event.
void ABaseDotaCharacter::SetCharacterState(ECharacterStates newState)
{
	characterState = newState;
	OnCharacterStateChanged.Broadcast();
}


/* Helper functions, including accessors and mutators */
#pragma region HELPERS
FORCEINLINE FDotaHeroAttributes* ABaseDotaCharacter::GetCharAttributes()
{
	return &attributes;
}

FORCEINLINE void ABaseDotaCharacter::ReInitializeChar()
{
	// Setup movement properties
	
	UCharacterMovementComponent* movementComponent = GetCharacterMovement();

	if (movementComponent)
	{
		movementComponent->MaxWalkSpeed = attributes.statsData.moveSpeed;
		movementComponent->MaxWalkSpeedCrouched = attributes.statsData.moveSpeed / 2.f;
		movementComponent->RotationRate = turnRate;
		
		movementComponent->JumpZVelocity = 300.0f;

		movementComponent->bOrientRotationToMovement = true;
	}
}
#pragma endregion


