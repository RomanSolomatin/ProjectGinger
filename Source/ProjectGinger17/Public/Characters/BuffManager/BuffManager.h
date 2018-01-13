// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffSystem/BaseBuff.h"
#include "BuffManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTGINGER17_API UBuffManager : public UActorComponent
{
	GENERATED_BODY()

#pragma region BUFF_MANAGER_MEMBERS
protected:

	// Map all Buff unique names to their associated Buff Modifier values.
	// We use Lists in case a modifier is stackable.
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Buff Manager")
	TMap<FString, TArray<UBaseBuff*>> activeBuffs;

#pragma endregion


#pragma region BUFF_MANAGER_METHODS

public:	
	// Sets default values for this component's properties
	UBuffManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Buff Manager Methods")
	bool AddBuff(UBaseBuff* buff);

	UFUNCTION(BlueprintCallable, Category = "Buff Manager Methods")
	bool AddBuffByType(TAssetSubclassOf<UBaseBuff> buff);

	UFUNCTION(BlueprintCallable, Category = "Buff Manager Methods")
	void RemoveBuff(FString buffName);


	

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEventBuffRemoved);

	UPROPERTY(BlueprintAssignable, Category = "Buff Manager Events")
	FEventBuffRemoved OnBuffRemoved;
	

#pragma endregion


		
	
};
