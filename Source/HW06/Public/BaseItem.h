// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OverlapInterface.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

class USphereComponent;

UCLASS()
class HW06_API ABaseItem : public AActor, public IOverlapInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	FName ItemType;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USphereComponent* Collision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	USoundBase* PickupSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	UParticleSystem* PickupParticle;

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

	virtual void DestroyItem();
	FName GetItemType() const;
};
