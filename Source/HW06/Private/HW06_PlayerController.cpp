// Fill out your copyright notice in the Description page of Project Settings.


#include "HW06_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "HW06_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "LevelTextRow.h"


AHW06_PlayerController::AHW06_PlayerController() :
	InputMappingContext(nullptr),
	MoveAction(nullptr),
	LookAction(nullptr),
	JumpAction(nullptr),
	SprintAction(nullptr),
	HUDWidgetClass(nullptr),
	HUDWidgetInstance(nullptr),
	MainMenuWidgetClass(nullptr),
	MainMenuWidgetInstance(nullptr),
	FlashbangWidgetClass(nullptr),
	FlashbangWidgetInstance(nullptr),
	LevelUIWidgetClass(nullptr),
	LevelUIWidgetInstance(nullptr),
	bIsPIE(true)
{

}

void AHW06_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer()) 
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()) 
		{
			if (InputMappingContext) 
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}

	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains("MenuLevel")) 
	{
		ShowMainMenu(false);
	}
	// 레벨 UI
	else
	{
		if (UHW06_GameInstance* GameInstance = Cast<UHW06_GameInstance>(GetGameInstance()))
		{
			int32 CurrentLevelIndex = GameInstance->GetCurrentLevelIndex();
			ShowLevelUI(CurrentLevelIndex);
		}
	}
}

void AHW06_PlayerController::ShowMainMenu(bool bIsRestart) 
{
	// MainMenu 뷰포트 지우기
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}
	if (MainMenuWidgetClass)
	{
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();
			// 뒤에 레벨이 떠 있을때 마우스 포커스가 UI로만 가도록 지정
			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
		}

		if (UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"))))
		{
			if (bIsRestart)
			{
				ButtonText->SetText(FText::FromString(FString::Printf(TEXT("Restart"))));
			}
			else
			{
				ButtonText->SetText(FText::FromString(FString::Printf(TEXT("Start"))));
			}
		}
		if (bIsRestart)
		{
			if (UTextBlock* TitleText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("TitleText"))))
			{
				TitleText->SetVisibility(ESlateVisibility::Hidden);
			}
			if (UTextBlock* GameOverText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("GameOverText")))) 
			{
				GameOverText->SetVisibility(ESlateVisibility::Visible);
			}
			if (UTextBlock* TotalScoreText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("TotalCountText"))))
			{
				if (UHW06_GameInstance* CH3_GameInstance = Cast<UHW06_GameInstance>(UGameplayStatics::GetGameInstance(this)))
				{
					TotalScoreText->SetText(FText::FromString(FString::Printf(TEXT("Total Candy: %d"), CH3_GameInstance->GetTotalCandyCount())));
					TotalScoreText->SetVisibility(ESlateVisibility::Visible);
				}
			}
		}
	}
}
void AHW06_PlayerController::ShowGameHUD()
{
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}
	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
			bShowMouseCursor=false;
			SetInputMode(FInputModeGameOnly());
		}
	}
}

void AHW06_PlayerController::UpdateGameHUD(int32 CollectedCount, int32 SpawnedCount, int32 CurrentLevelIndex)
{
	if (HUDWidgetInstance)
	{
		if (UTextBlock* CollectedCountText = Cast<UTextBlock>(HUDWidgetInstance->GetWidgetFromName(TEXT("CollectedCandiesText"))))
		{
			CollectedCountText->SetText(FText::FromString(FString::Printf(TEXT("Colleted Candies: %d / %d"), CollectedCount, SpawnedCount)));
		}
		if (UTextBlock* LevelText = Cast<UTextBlock>(HUDWidgetInstance->GetWidgetFromName(TEXT("LevelText"))))
		{
			LevelText->SetText(FText::FromString(FString::Printf(TEXT("Level %d"), CurrentLevelIndex+1)));
		}
	}
}

void AHW06_PlayerController::StartGame() 
{
	if (UHW06_GameInstance* GameInstance = Cast<UHW06_GameInstance>(GetGameInstance())) 
	{
		GameInstance->SetCurrentLevelIndex(0);
		GameInstance->SetTotalCount(0);
		GameInstance->ResetRemainingLives();
	}
	UGameplayStatics::OpenLevel(GetWorld(), FName("Level1"));
	SetPause(false);
}
void AHW06_PlayerController::QuitGame()
{
	if (bIsPIE)
	{
		UKismetSystemLibrary::QuitGame(
			this,
			GetWorld()->GetFirstPlayerController(),
			EQuitPreference::Quit,
			false);
	}
	else
	{
		FGenericPlatformMisc::RequestExit(false);
	}
}

void AHW06_PlayerController::ShowFlashbangEffect()
{
	if (FlashbangWidgetClass)
	{
		FlashbangWidgetInstance = CreateWidget<UUserWidget>(this, FlashbangWidgetClass);
		if (FlashbangWidgetInstance)
		{
			FlashbangWidgetInstance->AddToViewport();
			UFunction* PlayAnimFunc = FlashbangWidgetInstance->FindFunction(FName("PlayFlashbangAnim"));
			if (PlayAnimFunc)
			{
				FlashbangWidgetInstance->ProcessEvent(PlayAnimFunc, nullptr);
			}
		}
	}
}
void AHW06_PlayerController::ShowLevelUI(int32 CurrentLevelIndex)
{
	if (LevelUIWidgetClass)
	{
		LevelUIWidgetInstance = CreateWidget<UUserWidget>(this, LevelUIWidgetClass);
		if (LevelUIWidgetInstance)
		{
			FLevelTextRow* LevelTextRow = GetLevelTextRow(CurrentLevelIndex);
			FString LevelName = LevelTextRow->LevelName;
			FString LevelAlert = LevelTextRow->LevelAlert;
			LevelUIWidgetInstance->AddToViewport();
			UFunction* PlayAnimFunc = LevelUIWidgetInstance->FindFunction(FName("PlayLevelUIAnim"));
			if (UTextBlock* LevelNameText = Cast<UTextBlock>(LevelUIWidgetInstance->GetWidgetFromName(TEXT("LevelNameText"))))
			{
				LevelNameText->SetText(FText::FromString(FString::Printf(TEXT("%s"), *LevelName)));
			}
			if (UTextBlock* LevelAlertText = Cast<UTextBlock>(LevelUIWidgetInstance->GetWidgetFromName(TEXT("LevelAlertText"))))
			{
				LevelAlertText->SetText(FText::FromString(FString::Printf(TEXT("%s"), *LevelAlert)));
			}
			
			if (PlayAnimFunc)
			{
				LevelUIWidgetInstance->ProcessEvent(PlayAnimFunc, nullptr);
			}
		}
	}
}

void AHW06_PlayerController::ShowAlertText()
{
	if (HUDWidgetInstance)
	{
		UFunction* PlayAlertAnimFunc = HUDWidgetInstance->FindFunction(FName("PlayAlertAnim"));
		if (PlayAlertAnimFunc)
		{
			HUDWidgetInstance->ProcessEvent(PlayAlertAnimFunc, nullptr);
		}
	}
}

FLevelTextRow* AHW06_PlayerController::GetLevelTextRow(int32 CurrentLevelIndex)
{
	if (!LevelTextDataTable) return nullptr;
	
	TArray<FLevelTextRow*> LevelTextRows;
	static const FString ContextString(TEXT("LevelTextRow"));
	LevelTextDataTable->GetAllRows(ContextString, LevelTextRows);
	if (LevelTextRows.IsEmpty()) return nullptr;

	for (FLevelTextRow* Row : LevelTextRows )
	{
		if (Row->LevelIndex == CurrentLevelIndex)
		{
			return Row;
		}
	}
	return nullptr;
}
