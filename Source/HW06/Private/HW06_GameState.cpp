// Fill out your copyright notice in the Description page of Project Settings.


#include "HW06_GameState.h"
#include "HW06_PlayerController.h"


void AHW06_GameState::BeginPlay() 
{
	Super::BeginPlay();


}
void AHW06_GameState::OnGameOver() 
{
	if (AHW06_PlayerController* PlayerController = Cast<AHW06_PlayerController>(GetWorld()->GetFirstPlayerController())) 
	{
		PlayerController->SetPause(true);
		PlayerController->ShowMainMenu(true);
	}
}
