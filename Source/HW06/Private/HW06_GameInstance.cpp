// Fill out your copyright notice in the Description page of Project Settings.


#include "HW06_GameInstance.h"

UHW06_GameInstance::UHW06_GameInstance() 
{
	TotalCandyCount = 0;
	MaxLives = 3;
	RemainingLives = MaxLives;
	CurrentLevelIndex = 0;
}

int32 UHW06_GameInstance::GetTotalCandyCount() const
{
	return TotalCandyCount;
}

int32 UHW06_GameInstance::GetRemainingLives() const
{
	return RemainingLives;
}
int32 UHW06_GameInstance::GetCurrentLevelIndex() const
{
	return CurrentLevelIndex;
}

void UHW06_GameInstance::AddToCount() 
{
	TotalCandyCount++;
	UE_LOG(LogTemp, Warning, TEXT("TotalCandyCount: %d"), TotalCandyCount);
}

void UHW06_GameInstance::LoseLife() 
{
	RemainingLives = FMath::Clamp(RemainingLives - 1, 0, MaxLives);
	UE_LOG(LogTemp, Warning, TEXT("Remaining Lives: %d"), RemainingLives);
}

void UHW06_GameInstance::SetCurrentLevelIndex(int32 LevelIndex)
{
	CurrentLevelIndex = LevelIndex;
	UE_LOG(LogTemp, Warning, TEXT("Current Level: %d"), CurrentLevelIndex);
}
void UHW06_GameInstance::SetTotalCount(int32 Count)
{
	TotalCandyCount = Count;
}
void UHW06_GameInstance::ResetRemainingLives()
{
	RemainingLives = MaxLives;
}