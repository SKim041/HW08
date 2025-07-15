// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingAutoObstacle.h"

AMovingAutoObstacle::AMovingAutoObstacle() 
{
	
}

void AMovingAutoObstacle::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	MoveObstacle(DeltaTime);
}