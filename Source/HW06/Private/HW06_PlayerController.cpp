// Fill out your copyright notice in the Description page of Project Settings.


#include "HW06_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "HW06_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"


AHW06_PlayerController::AHW06_PlayerController() :
	InputMappingContext(nullptr),
	MoveAction(nullptr),
	LookAction(nullptr),
	JumpAction(nullptr),
	SprintAction(nullptr),
	HUDWidgetClass(nullptr),
	HUDWidgetInstance(nullptr),
	MainMenuWidgetClass(nullptr),
	MainMenuWidgetInstance(nullptr)
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
	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());
}