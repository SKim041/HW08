// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "HealingItem.generated.h"

UCLASS()
class HW06_API AHealingItem : public ABaseItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHealingItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 HealAmount;

	virtual void ActivateActor(AActor* Activator) override;

};
