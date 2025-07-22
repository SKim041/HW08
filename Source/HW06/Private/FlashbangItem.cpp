// Fill out your copyright notice in the Description page of Project Settings.


#include "FlashbangItem.h"
#include "HW06_PlayerController.h"


// Sets default values
AFlashbangItem::AFlashbangItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ItemType="FlashBangItem";
}

void AFlashbangItem::ActivateActor(AActor* Activator)
{
	Super::ActivateActor(Activator);
	if (AHW06_PlayerController* PlayerController = Cast<AHW06_PlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PlayerController->ShowFlashbangEffect();
	}
	DestroyItem();
}
