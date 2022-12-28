// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectibleItems/Crystal.h"
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystemComponent.h>
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "Player/PlayerCharacter.h"

// Sets default values
ACrystal::ACrystal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	Mesh->SetupAttachment(RootComponent);
}


// Called when the game starts or when spawned
void ACrystal::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ACrystal::OnOverlapBegin);
}

// Called every frame
void ACrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACrystal::OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->IsA(APlayerCharacter::StaticClass()))
		{
			APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);

			if (Player)
			{
				UParticleSystemComponent* ParticleSystem = UGameplayStatics::SpawnEmitterAtLocation(this, PickedUpEffect, GetActorLocation(), FRotator::ZeroRotator, true);

				Player->SetCollectedCrystals();
				Player->SetHealth(15.f);

				FTimerHandle TimerHandle;
				GetWorldTimerManager().SetTimer(TimerHandle, ParticleSystem, &UParticleSystemComponent::Deactivate, 3.0f, false);

				Destroy();
			}
		}
	}
}
