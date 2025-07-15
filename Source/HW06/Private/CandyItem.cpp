// Fill out your copyright notice in the Description page of Project Settings.


#include "CandyItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HW06_GameMode.h"

// Sets default values
ACandyItem::ACandyItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Collision->SetupAttachment(RootComponent);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(Collision);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACandyItem::OnActorOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ACandyItem::OnActorEndOverlap);

	PickupSound = nullptr;
}

void ACandyItem::OnActorOverlap(
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

void ACandyItem::OnActorEndOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex) 
{
}

void ACandyItem::ActivateActor(AActor* Activator)
{
	if (AHW06_GameMode* GameMode = Cast<AHW06_GameMode>(GetWorld()->GetAuthGameMode())) 
	{
		GameMode->OnCandyCollected();
	}

	if (PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			PickupSound,
			GetActorLocation()
		);
	}
	Destroy();
}

