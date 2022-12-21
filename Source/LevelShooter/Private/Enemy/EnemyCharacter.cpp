// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyCharacter.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ManageAnimation();
}

void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool AEnemyCharacter::IsMoving()
{
	FVector Velocity = GetVelocity();
	double Movement = Velocity.SizeSquared();

	return Movement > 0;
}

void AEnemyCharacter::ManageAnimation()
{
	if (IsMoving()) {
		EnemySpeedAnimation = 100;
		EnemyAngleAnimation = 50;
	}
	else {
		EnemySpeedAnimation = 25;
		EnemyAngleAnimation = 50;
	}
}

