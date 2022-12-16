// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableItems/LiftPlartform.h"

ALiftPlartform::ALiftPlartform()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
}

void ALiftPlartform::BeginPlay()
{
	Super::BeginPlay();
}

void ALiftPlartform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALiftPlartform::ManageLift(bool bUp)
{
	FVector NewLocation = GetActorLocation();

	if (bUp) {
		NewLocation.Z += 110.0f;
	}
	else {
		NewLocation.Z -= 110.0f;
	}

	SetActorLocation(NewLocation);
}
