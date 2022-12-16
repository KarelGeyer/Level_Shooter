// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableItems/Lever.h"
#include "InteractableItems/LiftPlartform.h"
#include <Subsystems/PanelExtensionSubsystem.h>
#include "Blueprint/UserWidget.h"
#include <Kismet/GameplayStatics.h>

ALever::ALever()
{
	PrimaryActorTick.bCanEverTick = true;

	// Setup Mesh as default root component
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = BaseMesh;

	HandleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Handle_Mesh"));
	HandleMesh->SetupAttachment(RootComponent);

	RootComponent->SetMobility(EComponentMobility::Static);
	HandleMesh->SetMobility(EComponentMobility::Movable);
}

void ALever::BeginPlay()
{
	Super::BeginPlay();

	SetActorLabel("Lever");
}

void ALever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALever::OnPlayerInteraction()
{
	GetAttachedActors(Children);

	if (!IsPulled)
	{
		FRotator NewRotation = FRotator(0.0f, 0.0f, -60.0f);
		HandleMesh->SetRelativeRotation(NewRotation);
		IsPulled = true;

		if (Children.Num() == 0) {
			return;
		}

		for (AActor* Child : Children)
		{
			if (Child != nullptr) {
				if (Child->IsA(ALiftPlartform::StaticClass())) {
					ALiftPlartform* LiftPlatform = Cast<ALiftPlartform>(Child);
					if (LiftPlatform == nullptr) {
						return;
					}

					LiftPlatform->ManageLift(true);
				}
			}
		}
	}
	else
	{
		FRotator NewRotation = FRotator(0.0f, 0.0f, 60.0f);
		HandleMesh->SetRelativeRotation(NewRotation);
		IsPulled = false;

		if (Children.Num() == 0) {
			return;
		}

		for (AActor* Child : Children)
		{
			if (Child != nullptr) {
				if (Child->IsA(ALiftPlartform::StaticClass())) {
					ALiftPlartform* LiftPlatform = Cast<ALiftPlartform>(Child);
					if (LiftPlatform == nullptr) {
						return;
					}

					LiftPlatform->ManageLift(false);
				}
			}
		}
	}
}
