// Fill out your copyright notice in the Description page of Project Settings.


#include "LiftPlartform.h"

// Sets default values
ALiftPlartform::ALiftPlartform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
}

void ALiftPlartform::Lift()
{
	FVector NewLocation = GetActorLocation();
	NewLocation.Z += 100.0f;
	SetActorLocation(NewLocation);
}

// Called when the game starts or when spawned
void ALiftPlartform::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALiftPlartform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

