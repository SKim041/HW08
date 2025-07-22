// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OverlapInterface.h"
#include "EndPoint.generated.h"

class USphereComponent;

UCLASS()
class HW06_API AEndPoint : public AActor, public IOverlapInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndPoint();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USphereComponent* Collision;

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
