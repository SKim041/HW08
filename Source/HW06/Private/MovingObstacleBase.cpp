// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingObstacleBase.h"

// Sets default values
AMovingObstacleBase::AMovingObstacleBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(SceneComp);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMovingObstacleBase::BeginPlay()
{
	Super::BeginPlay();
	// 처음 위치 저장
	OriginPosition = GetActorLocation();
	if (MoveVelocity == FVector::ZeroVector) 
	{
		MoveVelocity = FVector(0, 0, FMath::RandRange(100.0f, 150.0f));
	}
	if (FMath::IsNearlyZero(MoveDistance)) 
	{
		MoveDistance = FMath::RandRange(100.0f, 150.0f);
	}
}

// Called every frame
void AMovingObstacleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMovingObstacleBase::MoveObstacle(float DeltaTime) 
{
	FVector MoveOffset = MoveVelocity * DeltaTime;
	AddActorLocalOffset(MoveOffset, false);
	if (FVector::Dist(OriginPosition, GetActorLocation()) > MoveDistance) 
	{
		MoveVelocity = -MoveVelocity;
		OriginPosition = GetActorLocation();
	}
}

