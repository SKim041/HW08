// Fill out your copyright notice in the Description page of Project Settings.


#include "HW06_GameMode.h"
#include "HW06_Character.h"
#include "HW06_PlayerController.h"
#include "HW06_GameState.h"
#include "HW06_GameInstance.h"
#include "SpawnVolume.h"
#include "CandyItem.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"


AHW06_GameMode::AHW06_GameMode() 
{
	DefaultPawnClass = AHW06_Character::StaticClass();
	PlayerControllerClass = AHW06_PlayerController::StaticClass();
	GameStateClass = AHW06_GameState::StaticClass();
}


void AHW06_GameMode::BeginPlay() 
{
	Super::BeginPlay();
	StartLevel();
}
void AHW06_GameMode::StartLevel() 
{
	
	// 현재 레벨 
	if(UHW06_GameInstance* GameInstance= Cast<UHW06_GameInstance>(GetGameInstance()))
	{
		CurrentLevelIndex = GameInstance->GetCurrentLevelIndex();
	}
	// 레벨 별 맵 모듈 배치
	int32 Rows = CurrentLevelIndex + 2;
	int32 Cols = 2;
	for (int32 r = 0; r < Rows; r++) 
	{
		int32 c = FMath::RandRange(0, Cols-1);
		FVector SpawnPoint = FVector(1200+2400*r,-2400*c, 0);
		c = FMath::RandRange(0, 3);
		FRotator SpawnRotator = FRotator(0, 90 * c, 0);
		GetWorld()->SpawnActor<AActor>(MapModule, SpawnPoint, SpawnRotator);
	}
	
	// 아이템 스폰
	CollectedCandyCount = 0;
	SpawnedCandyCount = 0;

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);
	for (AActor* v : FoundVolumes) 
	{
		ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(v);

		for (int32 i = 0; i < CandyToSpawn; i++)
		{
			if (SpawnVolume) 
			{
				AActor* SpawnedActor = SpawnVolume->SpawnItem();
				if (SpawnedActor && SpawnedActor->IsA(ACandyItem::StaticClass())) 
				{
					SpawnedCandyCount++;
				}
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Spawned Candy Count: %d"), SpawnedCandyCount);
	
}

void AHW06_GameMode::EndLevel() 
{
	if (CollectedCandyCount == SpawnedCandyCount) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Success!")));

		OnGameOver();
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("%d candies left"), SpawnedCandyCount-CollectedCandyCount));

	}
}

void AHW06_GameMode::OnGameOver() 
{
	if (AHW06_GameState* HW06_GameState = GetGameState<AHW06_GameState>())
	{
		HW06_GameState->OnGameOver();
	}
}
void AHW06_GameMode::OnPlayerDeath(AController* DeadController) 
{
	APawn* OldPawn = DeadController->GetPawn();
	if (IsValid(OldPawn))
	{
		DeadController->UnPossess();
		OldPawn->Destroy();
	}
	if (UHW06_GameInstance* GameInstance = Cast<UHW06_GameInstance>(GetGameInstance())) 
	{
		GameInstance->LoseLife();
		if (GameInstance->GetRemainingLives() == 0) 
		{
			OnGameOver();
		}
		else 
		{
			RestartPlayerAtPlayerStart(DeadController, ChoosePlayerStart(DeadController));
		}
	}
}

void AHW06_GameMode::OnCandyCollected() 
{
	CollectedCandyCount++;
	if (UHW06_GameInstance* GameInstance = Cast<UHW06_GameInstance>(GetGameInstance()))
	{
		GameInstance->AddToCount();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Fail to find GameInstance"));
	}
}