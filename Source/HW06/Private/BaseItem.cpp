// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABaseItem::ABaseItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);
	Collision=CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Collision->SetupAttachment(RootComponent);
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(Collision);
	
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnActorOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnActorEndOverlap);

	PickupSound = nullptr;
	PickupParticle=nullptr;
}

void ABaseItem::OnActorOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		ActivateActor(OtherActor);
	}
}

void ABaseItem::OnActorEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ABaseItem::ActivateActor(AActor* Activator)
{
	if (PickupParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			PickupParticle,
			GetActorLocation(),
			GetActorRotation(),
			true
		);
	}
	if (PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			PickupSound,
			GetActorLocation()
		);
	}
}

void ABaseItem::DestroyItem()
{
	Destroy();	
}

FName ABaseItem::GetItemType() const
{
	return ItemType;
}




