// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RotatingObstacleBase.h"
#include "RotatingAutoObstacle.generated.h"

/**
 * 
 */
UCLASS()
class HW06_API ARotatingAutoObstacle : public ARotatingObstacleBase
{
	GENERATED_BODY()
public:
	ARotatingAutoObstacle();

	virtual void Tick(float DeltaTime) override;
	
};
