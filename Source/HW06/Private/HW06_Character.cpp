// Fill out your copyright notice in the Description page of Project Settings.


#include "HW06_Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HW06_PlayerController.h"
#include "HW06_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "Components/RichTextBlock.h"
#include "HW06_GameInstance.h"

// Sets default values
AHW06_Character::AHW06_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadHP"));
	OverheadWidget->SetupAttachment(GetMesh());
	OverheadWidget->SetWidgetSpace(EWidgetSpace::Screen);	

	// Movement 초기화
	NormalSpeed = 200.0f;
	SprintMultiplier = 1.7f;
	MouseSensitivity = 1.0f;
}

// Called when the game starts or when spawned
void AHW06_Character::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	
	UpdateOverheadHP();
}

// Called every frame
void AHW06_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 캐릭터 정지 시 물체 통과 방지
	FHitResult OutHit;
	GetCharacterMovement()->SafeMoveUpdatedComponent(FVector(0.f, 0.f, 0.01f), GetActorRotation(), true, OutHit);
	GetCharacterMovement()->SafeMoveUpdatedComponent(FVector(0.f, 0.f, -0.01f), GetActorRotation(), true, OutHit);

	if (GetActorLocation().Z < -100) 
	{
		Die();
		UE_LOG(LogTemp, Display, TEXT("Die"));
	}

}

void AHW06_Character::Die() 
{
	if (AHW06_GameMode* GameMode = Cast<AHW06_GameMode>(UGameplayStatics::GetGameMode(this))) 
	{
		GameMode->OnPlayerDeath(GetController());
	}
}
void AHW06_Character::UpdateOverheadHP() 
{
	if (!OverheadWidget) return;
	UUserWidget* OverheadWidgetInstance = OverheadWidget->GetUserWidgetObject();
	if (!OverheadWidgetInstance) return;

	if (URichTextBlock* HPText = Cast<URichTextBlock>(OverheadWidgetInstance->GetWidgetFromName(TEXT("HPText")))) 
	{
		if (UHW06_GameInstance* GameInstance = Cast<UHW06_GameInstance>(GetGameInstance())) 
		{
			FString HPString;
			for (int32 i = 0; i < GameInstance->GetRemainingLives(); i++) 
			{
				HPString += TEXT("\u2764\uFE0F");
			}
			UE_LOG(LogTemp, Warning, TEXT("update hp: %d"), GameInstance->GetRemainingLives());
			HPText->SetText(FText::FromString(HPString));
		}
	}
}
// Called to bind functionality to input
void AHW06_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		if (AHW06_PlayerController* PlayerController = Cast<AHW06_PlayerController>(GetController())) 
		{
			if (PlayerController->MoveAction) 
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AHW06_Character::Move
				);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AHW06_Character::Look
				);
			}
			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered,
					this,
					&AHW06_Character::StartJump
				);
			}
			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,
					this,
					&AHW06_Character::StopJump
				);
			}
			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&AHW06_Character::StartSprint
				);
			}
			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&AHW06_Character::StopSprint
				);
			}
		}
	}

}

void AHW06_Character::Move(const FInputActionValue& Value) 
{
	if (!Controller) return;
	const FVector2D MoveInput = Value.Get<FVector2D>();
	if (!FMath::IsNearlyZero(MoveInput.X)) 
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}
void AHW06_Character::Look(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();
	AddControllerYawInput(LookInput.X * MouseSensitivity);
	AddControllerPitchInput(LookInput.Y * MouseSensitivity);
}
void AHW06_Character::StartJump(const FInputActionValue& Value)
{
	if (Value.Get<bool>()) 
	{
		Jump();
	}
}
void AHW06_Character::StopJump(const FInputActionValue& Value)
{
	if (!Value.Get<bool>())
	{
		StopJumping();
	}
}
void AHW06_Character::StartSprint(const FInputActionValue& Value)
{
	if (GetCharacterMovement()) 
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed * SprintMultiplier;
	}
}
void AHW06_Character::StopSprint(const FInputActionValue& Value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
}