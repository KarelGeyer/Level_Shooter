// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Lever.h"
#include "GameFramework/Character.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Lever = Cast<ALever>(UGameplayStatics::GetActorOfClass(GetWorld(), ALever::StaticClass()));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Animate();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move_Forward"), this, &APlayerCharacter::Move);
	PlayerInputComponent->BindAxis(TEXT("Move_Right"), this, &APlayerCharacter::Rotate);
	PlayerInputComponent->BindAxis(TEXT("Look_Up"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("Look_Right"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &APlayerCharacter::Interact);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &APlayerCharacter::Run);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &APlayerCharacter::StopRunning);
}


void APlayerCharacter::Move(float Value)
{
	FVector CharLocation = FVector::ZeroVector;
	CharLocation.X = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed;
	AddActorLocalOffset(CharLocation, true);
}

void APlayerCharacter::Rotate(float Value)
{
	FVector CharRotation = FVector::ZeroVector;
	CharRotation.Y = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed;
	AddActorLocalOffset(CharRotation, true);
}

void APlayerCharacter::Run()
{
	if (IsWalkingForwards) {
		Speed = 600;
	}
}

void APlayerCharacter::StopRunning()
{
	Speed = 200;
}


bool APlayerCharacter::RayCastTrace(FHitResult& Hit, FVector& ShotDirection)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController == nullptr) {
		return false;
	}

	FVector Location;
	FRotator Rotation;
	PlayerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();

	FVector End = Location + Rotation.Vector() * 800;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

void APlayerCharacter::Interact()
{
	if (Lever->isPlayerInRange()) {
		InteractWithLever();
	}
}

void APlayerCharacter::InteractWithLever()
{
	Lever->OnPlayerInteraction();
}

void APlayerCharacter::Animate()
{
	if (CanJump()) {
		if (IsWalkingForwards && !IsRunning) {
			SpeedAnimation = 50.f;
			DirectionAnimation = 100.f;
		}

		if (IsWalkingForwards && IsRunning) {
			SpeedAnimation = 100.f;
			DirectionAnimation = 100.f;
		}

		if (IsWalkingBackwards) {
			SpeedAnimation = 50.f;
			DirectionAnimation = 0.f;
		}
	}
	else {
		SpeedAnimation = 0.f;
	}

	if (!IsWalkingForwards && !IsWalkingBackwards) {
		SpeedAnimation = 0.f;
	}
}


void APlayerCharacter::OnKeyDown(const FKey& Key) {
	if (Key == EKeys::W)
	{
		IsWalkingForwards = true;
	}

	if (Key == EKeys::S)
	{
		IsWalkingBackwards = true;
	}

	if (Key == EKeys::LeftShift) {
		IsRunning = true;
	}
}

void APlayerCharacter::OnKeyUp(const FKey& Key)
{
	if (Key == EKeys::W)
	{
		IsWalkingForwards = false;
	}

	if (Key == EKeys::S)
	{
		IsWalkingBackwards = false;
	}

	if (Key == EKeys::LeftShift) {
		IsRunning = false;
	}
}
