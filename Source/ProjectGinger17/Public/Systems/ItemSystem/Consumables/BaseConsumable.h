// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSystem/Interfaces/IConsumable.h"
#include "BaseConsumable.generated.h"

UCLASS(Abstract)
class PROJECTGINGER17_API ABaseConsumable : public AActor, public IConsumable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseConsumable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool Consume_Implementation(AActor* instigator) override;

	
	
};
