// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HW06_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FLevelTextRow;

UCLASS()
class HW06_API AHW06_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AHW06_PlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|HUD")
	TSubclassOf<UUserWidget> HUDWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|HUD")
	UUserWidget* HUDWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Menu")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|Menu")
	UUserWidget* MainMenuWidgetInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Effect")
	TSubclassOf<UUserWidget> FlashbangWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|Effect")
	UUserWidget* FlashbangWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Level")
	TSubclassOf<UUserWidget> LevelUIWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|Level")
	UUserWidget* LevelUIWidgetInstance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI|Level")
	UDataTable* LevelTextDataTable;

	UFUNCTION(BlueprintCallable, Category = "UI|Menu")
	void ShowMainMenu(bool bIsRestart);
	UFUNCTION(BlueprintCallable, Category = "UI|Menu")
	void ShowGameHUD();
	UFUNCTION(BlueprintCallable, Category = "UI|Menu")
	void UpdateGameHUD(int32 CollectedCount, int32 SpawnedCount, int32 CurrentLevelIndex);
	UFUNCTION(BlueprintCallable, Category = "UI|Menu")
	void StartGame();
	UFUNCTION(BlueprintCallable, Category = "UI|Menu")
	void QuitGame();
	UFUNCTION(BlueprintCallable, Category = "UI|Effect")
	void ShowFlashbangEffect();
	UFUNCTION(BlueprintCallable, Category = "UI|Menu")
	void ShowLevelUI(int32 CurrentLevelIndex);
	UFUNCTION(BlueprintCallable, Category = "UI|Effect")
	void ShowAlertText();
protected:
	virtual void BeginPlay() override;
	bool bIsPIE;

	FLevelTextRow* GetLevelTextRow(int32 CurrentLevelIndex);
};
