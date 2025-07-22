// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingItem.h"
#include "HW06_GameMode.h"
#include "HW06_Character.h"


// Sets default values
AHealingItem::AHealingItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	HealAmount=1;
}
void AHealingItem::ActivateActor(AActor* Activator)
{
	Super::ActivateActor(Activator);
	if (AHW06_GameMode* GameMode = Cast<AHW06_GameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->AddLives(HealAmount);
	}
	if (AHW06_Character* Player = Cast<AHW06_Character>(Activator))
	{
		Player->UpdateOverheadHP();
	}
	DestroyItem();
}

