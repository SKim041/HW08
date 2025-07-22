// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "TrackingProjectile.generated.h"

UCLASS()
class HW06_API ATrackingProjectile : public ABaseItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrackingProjectile();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USphereComponent* ExplosionCollision;
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category = "Item|Tracking")
	float TrackingTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Tracking")
	float TrackingInterpSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	UParticleSystem* ExplosionParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	USoundBase* ExplosionSound;
	
	bool bIsTracking;
	FVector PlayerLocation;

	UFUNCTION()
	void OnExplosionCollisionOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
	void Explode(AActor* Activator);

	virtual void ActivateActor(AActor* Activator) override;	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
