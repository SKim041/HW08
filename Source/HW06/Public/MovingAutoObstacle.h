// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingObstacleBase.h"
#include "MovingAutoObstacle.generated.h"

/**
 * 
 */
UCLASS()
class HW06_API AMovingAutoObstacle : public AMovingObstacleBase
{
	GENERATED_BODY()

public:
	AMovingAutoObstacle();

	virtual void Tick(float DeltaTime) override;
	
};
