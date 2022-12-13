// Fill out your copyright notice in the Description page of Project Settings.


#include "Crystal.h"
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystemComponent.h>
#include "GameFramework/PlayerController.h"
#include "PlayerCharacter.h"
#include "TimerManager.h"

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
		// check if the other actor is the player
		if (OtherActor->IsA(APlayerCharacter::StaticClass()))
		{
			// cast the other actor to the player character
			APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);

			if (Player)
			{
				UParticleSystemComponent* ParticleSystem = UGameplayStatics::SpawnEmitterAtLocation(this, PickedUpEffect, GetActorLocation(), FRotator::ZeroRotator, true);

				FTimerHandle TimerHandle;
				GetWorldTimerManager().SetTimer(TimerHandle, ParticleSystem, &UParticleSystemComponent::Deactivate, 3.0f, false);

				Destroy();
			}
		}
	}
}
