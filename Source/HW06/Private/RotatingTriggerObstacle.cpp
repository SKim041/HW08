// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingTriggerObstacle.h"
#include "Components/BoxComponent.h"

ARotatingTriggerObstacle::ARotatingTriggerObstacle() 
{
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Collision->SetupAttachment(RootComponent);

	StaticMeshComp->SetupAttachment(Collision);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ARotatingTriggerObstacle::OnActorOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ARotatingTriggerObstacle::OnActorEndOverlap);

	bIsTriggered = false;

}

void ARotatingTriggerObstacle::OnActorOverlap(
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

void ARotatingTriggerObstacle::OnActorEndOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
}

void ARotatingTriggerObstacle::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	RotateObstacle(DeltaTime);
}

void ARotatingTriggerObstacle::ActivateActor(AActor* Activator)
{
	if (!bIsTriggered) 
	{
		float Size = FVector(RotationVelocity.Pitch, RotationVelocity.Yaw, RotationVelocity.Roll).Size();
		FRotator TempRotator;
		TArray<int32> EmptyAxis;
		if (FMath::IsNearlyZero(RotationVelocity.Pitch)) EmptyAxis.Add(0);
		if (FMath::IsNearlyZero(RotationVelocity.Yaw)) EmptyAxis.Add(1);
		if (FMath::IsNearlyZero(RotationVelocity.Roll)) EmptyAxis.Add(2);

		if (EmptyAxis.Num() > 0) 
		{
			int32 RandomIndex = EmptyAxis[FMath::RandRange(0, EmptyAxis.Num() - 1)];
			switch (RandomIndex)
			{
			case 0:
				TempRotator.Pitch = Size;
				break;
			case 1:
				TempRotator.Yaw = Size;
				break;
			case 2:
				TempRotator.Roll = Size;
				break;
			}
			RotationVelocity = TempRotator;

		}
		
	}
	
	bIsTriggered = true;

}