// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "HW06_GameState.generated.h"

/**
 * 
 */
UCLASS()
class HW06_API AHW06_GameState : public AGameState
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	void OnGameOver();
};
