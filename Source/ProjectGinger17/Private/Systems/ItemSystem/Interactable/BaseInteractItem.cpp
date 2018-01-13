// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemSystem/Interactable/BaseInteractItem.h"

void ABaseInteractItem::Interact_Implementation(AActor * instigator)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("USED INTERACTABLE"));
	Execute_OnBeginInteract(this, instigator);
}

bool ABaseInteractItem::OnBeginInteract_Implementation(AActor * instigator)
{
	return false;
}

bool ABaseInteractItem::OnEndInteract_Implementation()
{
	return false;
}
