// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableItems/Teleport.h"
#include <Kismet/GameplayStatics.h>
#include "Player/PlayerCharacter.h"
#include "Components/BoxComponent.h"


// Sets default values
ATeleport::ATeleport()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = BaseMesh;

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATeleport::BeginPlay()
{
	Super::BeginPlay();

	SetActorLabel("Teleport");
}

// Called every frame
void ATeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATeleport::OnPlayerInteraction()
{
	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->SetActorLocation(TeleportLocation);
}

