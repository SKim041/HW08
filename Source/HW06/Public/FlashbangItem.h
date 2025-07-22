// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "FlashbangItem.generated.h"

UCLASS()
class HW06_API AFlashbangItem : public ABaseItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFlashbangItem();

protected:

	virtual void ActivateActor(AActor* Activator) override;
};
