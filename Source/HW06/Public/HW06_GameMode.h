// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "HW06_GameMode.generated.h"

UCLASS()
class HW06_API AHW06_GameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AHW06_GameMode();
	virtual void BeginPlay() override;
	void StartLevel();
	void EndLevel();
	void OnGameOver();
	void OnPlayerDeath(AController* DeadController);
	void OnCandyCollected();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 CandyToSpawn = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AActor> MapModule;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;

	int32 CollectedCandyCount;
	int32 SpawnedCandyCount;
	int32 CurrentLevelIndex;
};
