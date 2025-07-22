// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

struct FSpawnRow;
class UBoxComponent;

UCLASS()
class HW06_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	UBoxComponent* SpawningBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	UDataTable* ItemDataTable;

	FVector GetRandomPointInVolume() const;
	AActor* SpawnItem(TSubclassOf<AActor> ItemClass);
	FSpawnRow* GetRandomItemByLevel(int32 Level) const;
	void SpawnRandomItemByLevel(int32 Level);


};
