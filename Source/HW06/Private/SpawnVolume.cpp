// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"

#include "ContentBrowserItemData.h"
#include "Components/BoxComponent.h"
#include "SpawnRow.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(RootComponent);

	ItemDataTable = nullptr;
}

FVector ASpawnVolume::GetRandomPointInVolume() const 
{
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	return BoxOrigin + FVector(
		FMath::RandRange(-BoxExtent.X, BoxExtent.X),
		FMath::RandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::RandRange(-BoxExtent.Z, BoxExtent.Z)
	);
}
AActor* ASpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass) 
{
	if (!ItemClass) return nullptr;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

	return GetWorld()->SpawnActor<AActor>(
		ItemClass,
		GetRandomPointInVolume(),
		FRotator::ZeroRotator
	);
}

FSpawnRow* ASpawnVolume::GetRandomItemByLevel(int32 Level) const
{
	if (!ItemDataTable) return nullptr;

	TArray<FSpawnRow*> RandomItems;
	static const FString ContextString(TEXT("ItemSpawnRow"));
	ItemDataTable->GetAllRows(ContextString, RandomItems);

	if (RandomItems.IsEmpty()) return nullptr;

	float TotalChance = 0.0f;
	
	for (int32 i = 0; i < RandomItems.Num(); )
	{
		FSpawnRow* Row = RandomItems[i];
		if (Row && Row->MinSpawnLevel<=Level+1)
		{
			TotalChance+=Row->SpawnChance;
			i++;
		}
		else if (Row && Row->MinSpawnLevel>Level+1)
		{
			RandomItems.RemoveSingleSwap(Row);
		}
	}

	const float RandomValue = FMath::FRandRange(0.0f, TotalChance);
	float CurrentChance = 0.0f;
	for (FSpawnRow* Row:RandomItems)
	{
		if (Row)
		{
			CurrentChance+=Row->SpawnChance;
			if (RandomValue <= CurrentChance)
			{
				return Row;
			}
		}
	}
	return nullptr;
}

void ASpawnVolume::SpawnRandomItemByLevel(int32 Level)
{
	if (FSpawnRow* RandomItem = GetRandomItemByLevel(Level))
	{
		if (UClass* ActualClass=RandomItem->ActorClass.Get())
		{
			SpawnItem(ActualClass);
		}
	}
}



