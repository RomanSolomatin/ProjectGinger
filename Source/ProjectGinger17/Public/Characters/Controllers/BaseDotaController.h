#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Controllers/GazeManager/GazeManager.h"
#include "BaseDotaController.generated.h"

/** Base Dota Controller
 * The Base Dota Controller is a type of player controller that 
 * is responsible for issuing movement inputs for all Dota characters.
 * For UI and player specific features, derive further to a PlayerDotaController
 */
UCLASS()
class PROJECTGINGER17_API ABaseDotaController : public APlayerController
{
	GENERATED_BODY()


#pragma region CONTROLLER_VARIABLES
protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Dota Controller Components")
	UGazeManager* gazeManager;

private:

	AActor* usableActor;

	// Cache the Actor currently overlapped for processing.
	AActor* overlappedActor;

#pragma endregion


public:

	ABaseDotaController();

	// Handle Action and Axis Mapping for the Player Controller.
	// Use to Define basic movement and combat input.
	void SetupInputComponent();

	UFUNCTION(BlueprintImplementableEvent, Category = "Dota Controller UI")
	void DisplayNotification(const FString &text);

	UFUNCTION(BlueprintImplementableEvent, Category = "Dota Controller UI")
	void ClearNotifications();

protected:

	// Handle all raycasting to detect all interactable objects around the player
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	FORCEINLINE void MoveForward(float scale);
	FORCEINLINE void MoveRight(float scale);

	FORCEINLINE void Turn(float scale);
	FORCEINLINE void LookUp(float scale);

	FORCEINLINE void Jump();
	FORCEINLINE void StopJump();

	FORCEINLINE void AutoAttack();
	FORCEINLINE void StopAutoAttack();
	FORCEINLINE void SpecialAttack();
	FORCEINLINE void StopSpecialAttack();

	FORCEINLINE void Use();

#pragma region EVENT_HANDLERS
	void FocusObjectChangedHandler(FGazeEventData eventData);
	void FocusObjectLostHandler();

	// Must be UFUNCTIONS for reflection to recognize these functions to bind with Overlap events.
	UFUNCTION()
	void OnBeginActorOverlap(AActor* thisActor, AActor* otherActor);
	UFUNCTION()
	void OnEndActorOverlap(AActor* thisActor, AActor* otherActor);
#pragma endregion

};
