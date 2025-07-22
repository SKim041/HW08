// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingObstacleBase.generated.h"

UCLASS()
class HW06_API ARotatingObstacleBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingObstacleBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USceneComponent* SceneComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FRotator RotationVelocity;
	

	virtual void RotateObstacle(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
