// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingAutoObstacle.h"

ARotatingAutoObstacle::ARotatingAutoObstacle() 
{
}

void ARotatingAutoObstacle::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	RotateObstacle(DeltaTime);
}