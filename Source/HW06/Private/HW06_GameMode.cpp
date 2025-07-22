// Fill out your copyright notice in the Description page of Project Settings.


#include "HW06_GameMode.h"
#include "HW06_Character.h"
#include "HW06_PlayerController.h"
#include "HW06_GameState.h"
#include "HW06_GameInstance.h"
#include "SpawnVolume.h"
#include "CandyItem.h"
#include "SpawnRow.h"
#include "Kismet/GameplayStatics.h"


AHW06_GameMode::AHW06_GameMode() 
{
	DefaultPawnClass = AHW06_Character::StaticClass();
	PlayerControllerClass = AHW06_PlayerController::StaticClass();
	GameStateClass = AHW06_GameState::StaticClass();

	MapModuleDataTable = nullptr;
	CandyItem = nullptr;
	MaxLevel=3;
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
	const int32 Rows = CurrentLevelIndex + 2;
	const int32 Cols = 2;
	for (int32 r = 0; r < Rows; r++) 
	{
		int32 c = FMath::RandRange(0, Cols-1);
		FVector SpawnPoint = FVector(1200+2400*r,-2400*c, 0);
		c = FMath::RandRange(0, 3);
		FRotator SpawnRotator = FRotator(0, 90 * c, 0);
		GetWorld()->SpawnActor<AActor>(GetRandomMapModule(), SpawnPoint, SpawnRotator);
	}
	
	// 아이템 스폰
	CollectedCandyCount = 0;
	SpawnedCandyCount = 0;
	ItemToSpawn += pow(2, CurrentLevelIndex); 
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);
	for (AActor* v : FoundVolumes) 
	{
		ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(v);
		if (SpawnVolume->ActorHasTag("Candy"))
		{
			for (int32 i = 0; i < CandyToSpawn; i++)
			{
				if (SpawnVolume) 
				{
					AActor* SpawnedActor = SpawnVolume->SpawnItem(CandyItem);
					if (SpawnedActor && SpawnedActor->IsA(ACandyItem::StaticClass())) 
					{
						SpawnedCandyCount++;
					}
				}
			}
		}
		else
		{
			for (int32 i = 0; i < ItemToSpawn; i++)
			{
				if (SpawnVolume)
				{
					SpawnVolume->SpawnRandomItemByLevel(CurrentLevelIndex);
				}
			}
		}		
	}
	if (AHW06_PlayerController* PlayerController = Cast<AHW06_PlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PlayerController->ShowGameHUD();
		PlayerController->UpdateGameHUD(CollectedCandyCount, SpawnedCandyCount, CurrentLevelIndex);
	}
	
	
}

void AHW06_GameMode::EndLevel() 
{
	if (CollectedCandyCount == SpawnedCandyCount) 
	{
		CurrentLevelIndex++;
		if (UHW06_GameInstance* GameInstance = Cast<UHW06_GameInstance>(GetGameInstance()))
		{
			GameInstance->SetCurrentLevelIndex(CurrentLevelIndex);
		}
		if (CurrentLevelIndex>=MaxLevel)
		{
			OnGameOver();
			return;
		}
		if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
		{
			UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
		}
		else
		{
			OnGameOver();
		}
	}
	else 
	{
		if (AHW06_PlayerController* PlayerController = Cast<AHW06_PlayerController>(GetWorld()->GetFirstPlayerController()))
		{
			PlayerController->ShowAlertText();
		}
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
	if (DeadController)
	{
		AHW06_Character* OldCharacter = Cast<AHW06_Character>(DeadController->GetCharacter());
		if (IsValid(OldCharacter))
		{
			RespawnTransfrom = OldCharacter->GetRespawnTransform();
			DeadController->UnPossess();
			OldCharacter->Destroy();
		}
	}
	
	if (UHW06_GameInstance* GameInstance = Cast<UHW06_GameInstance>(GetGameInstance())) 
	{
		GameInstance->UpdateRemainingLives(-1);
		if (GameInstance->GetRemainingLives() == 0) 
		{
			OnGameOver();
		}
		else 
		{
			RestartPlayerAtTransform(DeadController, RespawnTransfrom);
		}
	}
}
void AHW06_GameMode::AddLives(int32 LivesChange)
{
	if (UHW06_GameInstance* GameInstance=Cast<UHW06_GameInstance>(GetGameInstance()))
	{
		GameInstance->UpdateRemainingLives(LivesChange);
	}
}
void AHW06_GameMode::OnCandyCollected() 
{
	CollectedCandyCount++;
	if (UHW06_GameInstance* GameInstance = Cast<UHW06_GameInstance>(GetGameInstance()))
	{
		GameInstance->AddToCount();
	}
	if (AHW06_PlayerController* PlayerController = Cast<AHW06_PlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PlayerController->UpdateGameHUD(CollectedCandyCount, SpawnedCandyCount, CurrentLevelIndex);
	}
}
TSubclassOf<AActor> AHW06_GameMode::GetRandomMapModule() const
{
	if (!MapModuleDataTable) return nullptr;
	TArray<FSpawnRow*> RandomMapModules;
	static const FString ContextString(TEXT("MapModuleSpawnRow"));
	MapModuleDataTable->GetAllRows(ContextString, RandomMapModules);
	if (RandomMapModules.IsEmpty()) return nullptr;
	float TotalChance=0.0f;
	for (int i=0; i<RandomMapModules.Num(); )
	{
		FSpawnRow* Row = RandomMapModules[i];
		if (Row && Row->MinSpawnLevel<=CurrentLevelIndex + 1)
		{
			TotalChance += Row->SpawnChance;
			i++;
		}
		else if (Row && Row->MinSpawnLevel>CurrentLevelIndex + 1)
		{
			RandomMapModules.RemoveSingleSwap(Row);
		}
	}

	const float RandomValue = FMath::FRandRange(0.0f, TotalChance);
	float CurrentChance = 0;
	for (FSpawnRow* Row : RandomMapModules)
	{
		if (Row)
		{
			CurrentChance += Row->SpawnChance;
			if (RandomValue <= CurrentChance)
			{
				return Row->ActorClass.Get();
			}
		}
	}
	return nullptr;
}

