// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelTextRow.generated.h"

USTRUCT(blueprintType)
struct FLevelTextRow: public FTableRowBase
{
	GENERATED_BODY();
public:
	UPROPERTY(editAnywhere, BlueprintReadWrite)
	int32 LevelIndex;
	UPROPERTY(editAnywhere, BlueprintReadWrite)
	FString LevelName;
	UPROPERTY(editAnywhere, BlueprintReadWrite)
	FString LevelAlert;
};
