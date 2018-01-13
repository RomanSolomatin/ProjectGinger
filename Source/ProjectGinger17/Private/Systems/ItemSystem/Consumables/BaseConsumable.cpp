// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemSystem/Consumables/BaseConsumable.h"


// Sets default values
ABaseConsumable::ABaseConsumable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseConsumable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseConsumable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABaseConsumable::Consume_Implementation(AActor * instigator)
{
	return false;
}

