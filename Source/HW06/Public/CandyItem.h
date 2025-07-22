// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "CandyItem.generated.h"

UCLASS()
class HW06_API ACandyItem : public ABaseItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACandyItem();



protected:

	virtual void ActivateActor(AActor* Activator) override;
};
