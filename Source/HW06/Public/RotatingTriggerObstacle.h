// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RotatingObstacleBase.h"
#include "OverlapInterface.h"
#include "RotatingTriggerObstacle.generated.h"

class UBoxComponent;
UCLASS()
class HW06_API ARotatingTriggerObstacle : public ARotatingObstacleBase, public IOverlapInterface
{
	GENERATED_BODY()
	
public:
	ARotatingTriggerObstacle();
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UBoxComponent* Collision;

	bool bIsTriggered;

	UFUNCTION()
	virtual void OnActorOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;
	UFUNCTION()
	virtual void OnActorEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;
	UFUNCTION()
	virtual void ActivateActor(AActor* Activator) override;

};
