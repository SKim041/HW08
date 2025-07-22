// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackingProjectile.h"
#include "HW06_Character.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ATrackingProjectile::ATrackingProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ExplosionCollision=CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ExplosionCollision->SetupAttachment(StaticMeshComp);

	ExplosionCollision->OnComponentBeginOverlap.AddDynamic(this, &ATrackingProjectile::OnExplosionCollisionOverlap);
	
	ExplosionParticle=nullptr;
	ExplosionSound=nullptr;
	
	TrackingTime=3.0f;
	TrackingInterpSpeed=5.0f;
	bIsTracking=false;
}

// Called every frame
void ATrackingProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsTracking)
	{
		FVector TargetLocation = FMath::VInterpTo(GetActorLocation(), PlayerLocation, DeltaTime, TrackingInterpSpeed);
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
		SetActorRotation(LookAtRotation);
		SetActorLocation(TargetLocation);
	}
}
void ATrackingProjectile::OnExplosionCollisionOverlap(
	UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		Explode(OtherActor);
	}
}

void ATrackingProjectile::Explode(AActor* OtherActor)
{
	if (ExplosionParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ExplosionParticle,
			GetActorLocation(),
			GetActorRotation(),
			true
			);
	}
	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			ExplosionSound,
			GetActorLocation()
		);
	}
	if (AHW06_Character* PlayerCharacter = Cast<AHW06_Character>(OtherActor))
	{
		PlayerCharacter->Die();
	}
	DestroyItem();
}

void ATrackingProjectile::ActivateActor(AActor* Activator)
{
	if (!bIsTracking)
	{
		Super::ActivateActor(Activator);
		UE_LOG(LogTemp, Warning, TEXT("Item Activated"));
		
		bIsTracking = true;
		FTimerHandle TrackingTimer;
		GetWorldTimerManager().SetTimer(TrackingTimer, this, &ATrackingProjectile::DestroyItem, TrackingTime, false);
	}
	PlayerLocation=Activator->GetActorLocation();
}
