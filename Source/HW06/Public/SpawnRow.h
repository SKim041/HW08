// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnRow.generated.h"


USTRUCT(blueprintType)
struct FSpawnRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ActorName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnChance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinSpawnLevel;
	
};
