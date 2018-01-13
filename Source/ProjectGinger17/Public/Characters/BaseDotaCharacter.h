// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DataTables/CharInfoTableRow.h"
#include "BaseDotaCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharacterStates : uint8
{Neutral, Combat, Interacting};

USTRUCT(BlueprintType)
struct FDotaHeroAttributes
{
	GENERATED_BODY()

public:
	// Hero Attributes
	/*
	* Attack Data
	* Regen Data
	* Stats Data
	*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Base Dota Character")
	FHeroAttackData attackData;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Base Dota Character")
	FHeroRegenData regenData;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Base Dota Character")
	FHeroStatsData statsData;
};

/*
* BaseDotaCharacter
* A base character class for NPCs and player controlled units that
* exhibit basic Dota related combat and navigational attributes (health, mana, movespeed, buffs, etc)
*/
UCLASS(BlueprintType)
class PROJECTGINGER17_API ABaseDotaCharacter : public ACharacter
{
	GENERATED_BODY()

#pragma region DELEGATES

public:
	// Multicast Delegates

	/* FStatsUpdated Delegate
	* To be called every second as the character stats are updated.
	*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStatsUpdated);

	/* FOnDeath Event
	* Called when the character's health reaches 0.
	* Can be extended to take arguments (i.e, cause of death)
	*/
	DECLARE_EVENT(ABaseDotaCharacter, FOnDeath);

	/* FOnStateChanged
	* Called when the character's enum CharacterState
	* is altered.
	*/
	DECLARE_EVENT(ABaseDotaCharacter, FOnStateChanged);

	// Called every second, when the character's stats are updated.
	UPROPERTY(BlueprintAssignable, Category = "Dota Character Events")
	FStatsUpdated StatsUpdated;

	FOnDeath OnDeathEvent;
	FOnStateChanged OnCharacterStateChanged;

#pragma endregion

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma region DOTA_CHARACTER_MEMBERS

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Basic Dota Attributes")
	FDotaHeroAttributes attributes;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Basic Dota Attributes", Meta = (DisplayName = "Current Health"))
	float currHealth;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Basic Dota Attributes", Meta = (DisplayName = "Current Mana"))
	float currMana;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = " Dota Motion Variables")
	FRotator turnRate;

	// The state of the character - i.e Idle/Neutral/Combat
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere, Category = "Basic Dota Attributes")
	ECharacterStates characterState;

	// The Buff Manager component that facilitates the application of buffs and debuffs on the character
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	class UBuffManager* buffManager;

	// The Inventory component that holds lists of categorized items and equipped items.
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	class UBaseInventory* inventory;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	class UStaticMeshComponent* equipSlot_L;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	class UStaticMeshComponent* equipSlot_R;

	bool bStrafe;

	/* Stores the socket names in the character's skeleton
	*  by ID numbers.
	* @ Id 1 = Left Hand
	* @ Id 2 = Right Hand
	* @ Id 3 = Back
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Basic Dota Attributes")
	TMap<int, UStaticMeshComponent*> socketMap;

private:

	// Used to manage the per second timer for the character
	FTimerHandle updateTimerHandler;

#pragma endregion

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

public:
	// Sets default values for this character's properties
	ABaseDotaCharacter();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// Called Every Second by the character's timer.
	// Updates the current stats based on the character's current
	// regenerative attributes.
	virtual void UpdateStats();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region EVENT_HANDLERS
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dota Character Events")
	void OnStatsUpdated();

	// Handler Function to when the Character State Enum changes. Does not need to be Callable,
	// as the invokation of the event should be handled exclusively internally.
	UFUNCTION(BlueprintImplementableEvent, Category = "Dota Character Events")
	void CharacterStateChangedHandler();
#pragma endregion

	// Allows components and other classes to modify the state of the character.
	// Invokes the OnCharacterStateChanged event.
	UFUNCTION(BlueprintCallable, Category = "Dota Character Methods")
	virtual void SetCharacterState(ECharacterStates newState);

	UFUNCTION(BlueprintCallable, Category = "Dota Character Methods")
	void SetEquipSlot(int socketId, UStaticMesh* _mesh);

	UFUNCTION(BlueprintCallable, Category = "Debug")
	void ToggleStrafe();


	// Returns a reference to the character's attribute struct.
	FORCEINLINE FDotaHeroAttributes* GetCharAttributes();

	/* Reinitialize Character - Helper Function
	*  Sets up and initializes values for the character's
	*  movement, stats, etc.
	*/
	FORCEINLINE void ReInitializeChar();
	
};
