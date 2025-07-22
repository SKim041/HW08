// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingObstacleBase.h"

// Sets default values
ARotatingObstacleBase::ARotatingObstacleBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(SceneComp);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARotatingObstacleBase::BeginPlay()
{
	Super::BeginPlay();
	if (RotationVelocity == FRotator::ZeroRotator) 
	{
		float RotationSpeed = FMath::RandRange(100.0f, 150.0f);
		if (FMath::RandRange(0, 1))
		{
			RotationSpeed *= -1;
		}
		RotationVelocity = FRotator(0, RotationSpeed, 0);
	}
}

// Called every frame
void ARotatingObstacleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARotatingObstacleBase::RotateObstacle(float DeltaTime) 
{
	AddActorLocalRotation(RotationVelocity * DeltaTime, true);
}

