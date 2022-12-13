// Fill out your copyright notice in the Description page of Project Settings.


#include "Lever.h"
#include "PlayerCharacter.h"
#include <Subsystems/PanelExtensionSubsystem.h>
#include "Blueprint/UserWidget.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ALever::ALever()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup Mesh as default root component
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = BaseMesh;

	HandleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Handle_Mesh"));
	HandleMesh->SetupAttachment(RootComponent);

	RootComponent->ComponentTags.Add(FName("Lever"));

	RootComponent->SetMobility(EComponentMobility::Static);
	HandleMesh->SetMobility(EComponentMobility::Movable);
}

void ALever::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void ALever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isPlayerInRange()) {
		DisplayPullWidget();
	}
	else {
		DestroyPullWidget();
	}
}

bool ALever::isPlayerInRange()
{

	if (Player != nullptr)
	{
		FVector LeverLocation = GetActorLocation();
		FVector PlayerLocation = Player->GetActorLocation();

		float Distance = FVector::Dist(PlayerLocation, LeverLocation);

		if (Distance <= 200)
		{
			return true;
		}
	}

	return false;
}

void ALever::DisplayPullWidget()
{
	if (PullWidgetClass)
	{
		PullWidget = CreateWidget<UUserWidget>(GetWorld(), PullWidgetClass);

		if (PullWidget)
		{
			PullWidget->AddToViewport();
		}
	}
}

void ALever::DestroyPullWidget()
{
	if (PullWidget && PullWidget->IsVisible())
	{
		PullWidget->RemoveFromViewport();
	}
}

void ALever::OnPlayerInteraction()
{
	if (!IsPulled)
	{
		FRotator NewRotation = FRotator(0.0f, 0.0f, -60.0f);
		HandleMesh->SetRelativeRotation(NewRotation);
		IsPulled = true;
	}
	else
	{
		FRotator NewRotation = FRotator(0.0f, 0.0f, 60.0f);
		HandleMesh->SetRelativeRotation(NewRotation);
		IsPulled = false;
	}

}
