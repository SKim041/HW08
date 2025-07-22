// Fill out your copyright notice in the Description page of Project Settings.


#include "CandyItem.h"
#include "HW06_GameMode.h"

// Sets default values
ACandyItem::ACandyItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
}

void ACandyItem::ActivateActor(AActor* Activator)
{
	Super::ActivateActor(Activator);
	
	if (AHW06_GameMode* GameMode = Cast<AHW06_GameMode>(GetWorld()->GetAuthGameMode())) 
	{
		GameMode->OnCandyCollected();
	}


	DestroyItem();
}

