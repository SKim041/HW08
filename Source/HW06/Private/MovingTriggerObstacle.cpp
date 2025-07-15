// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingTriggerObstacle.h"
#include "Components/BoxComponent.h"

AMovingTriggerObstacle::AMovingTriggerObstacle() 
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Collision->SetupAttachment(RootComponent);

	StaticMeshComp->SetupAttachment(Collision);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AMovingTriggerObstacle::OnActorOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AMovingTriggerObstacle::OnActorEndOverlap);

	bIsTriggered = false;
	DestroyDelay = 1.0f;
}

void AMovingTriggerObstacle::OnActorOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult) 
{
	if (OtherActor && OtherActor->ActorHasTag("Player")) 
	{
		ActivateActor(OtherActor);
	}

}

void AMovingTriggerObstacle::OnActorEndOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex) 
{
}

void AMovingTriggerObstacle::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	if (!bIsTriggered) 
	{
		MoveObstacle(DeltaTime);
	}
	else 
	{
		if (FVector::Dist(OriginPosition, GetActorLocation()) <= MoveDistance) 
		{
			AddActorLocalOffset(RandomPosition * DeltaTime, false);
		}
	}
}

void AMovingTriggerObstacle::ActivateActor(AActor* Activator)
{
	if (!bIsTriggered) 
	{
		FTimerHandle DestroyTimerHandle;
		GetWorldTimerManager().SetTimer(
			DestroyTimerHandle,
			this,
			&AMovingTriggerObstacle::DestroyObstacle,
			DestroyDelay,
			false
		);
		float TriggeredSpeed = MoveVelocity.Size() * 5;
		UE_LOG(LogTemp, Warning, TEXT("Triggered Speed: %.1f"), TriggeredSpeed);

		OriginPosition = GetActorLocation();
		RandomPosition = FVector(FMath::FRandRange(-1.0f, 1.0f), FMath::FRandRange(-1.0f, 1.0f), FMath::FRandRange(-1.0f, 1.0f));
		RandomPosition = RandomPosition.GetSafeNormal() * TriggeredSpeed;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(RandomPosition.ToString()));

	}
	
	bIsTriggered = true;

}

void AMovingTriggerObstacle::DestroyObstacle() 
{
	Destroy();
}