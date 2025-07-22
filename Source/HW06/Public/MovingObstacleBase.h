// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingObstacleBase.generated.h"

UCLASS()
class HW06_API AMovingObstacleBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingObstacleBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USceneComponent* SceneComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector MoveVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveDistance;

	FVector OriginPosition;

	virtual void MoveObstacle(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
