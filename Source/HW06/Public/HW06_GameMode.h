// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "HW06_GameMode.generated.h"

struct FSpawnRow;

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
	void AddLives(int32 LivesChange);
	void OnCandyCollected();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 CandyToSpawn = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 ItemToSpawn = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	UDataTable* MapModuleDataTable;
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AActor> CandyItem;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxLevel;
	
	int32 CollectedCandyCount;
	int32 SpawnedCandyCount;
	int32 CurrentLevelIndex;
	
	FTransform RespawnTransfrom;

	TSubclassOf<AActor> GetRandomMapModule() const;
};
