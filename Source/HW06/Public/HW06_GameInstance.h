// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HW06_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HW06_API UHW06_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UHW06_GameInstance();

	UFUNCTION(BlueprintPure, Category = "GameData")
	int32 GetTotalCandyCount() const;
	UFUNCTION(BlueprintPure, Category = "GameData")
	int32 GetRemainingLives() const;
	UFUNCTION(BlueprintPure, Category = "GameData")
	int32 GetCurrentLevelIndex() const;


	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddToCount();
	UFUNCTION(BlueprintCallable, Category = "GameData")
	void LoseLife();
	UFUNCTION(BlueprintCallable, Category = "GameData")
	void SetCurrentLevelIndex(int32 LevelIndex);
	UFUNCTION(BlueprintCallable, Category = "GameData")
	void SetTotalCount(int32 Count);
	UFUNCTION(BlueprintCallable, Category = "GameData")
	void ResetRemainingLives();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 TotalCandyCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 MaxLives;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 RemainingLives;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 CurrentLevelIndex;
};
