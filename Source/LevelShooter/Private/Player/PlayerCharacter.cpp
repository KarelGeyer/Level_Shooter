// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "InteractableItems/Lever.h"
#include "InteractableItems/Teleport.h"
#include "GameFramework/Character.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include <Subsystems/PanelExtensionSubsystem.h>
#include "Blueprint/UserWidget.h"
#include "InteractableItems/Bullet.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);

	USkeletalMeshComponent* Skeleton = GetMesh();

	WeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponComponent"));
	WeaponComponent->AttachToComponent(Skeleton, FAttachmentTransformRules::KeepWorldTransform, TEXT("Weapon_Socket"));

	BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSpawnPoint"));
	BulletSpawnPoint->AttachToComponent(Skeleton, FAttachmentTransformRules::KeepWorldTransform, TEXT("Weapon_Socket"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnEndOverlap);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Animate();
}

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
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &APlayerCharacter::Shoot);
}

void APlayerCharacter::Shoot()
{
	FVector SpawnLocation = BulletSpawnPoint->GetComponentLocation();
	FRotator SpawnRotation = BulletSpawnPoint->GetComponentRotation();

	ABullet* Projectile = GetWorld()->SpawnActor<ABullet>(BulletClass, SpawnLocation, SpawnRotation);

	Projectile->SetOwner(this);
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
	if (bIsWalkingForwards) {
		if (bIsWalkingLeft || bIsWalkingRight) {
			Speed = 200;
		}

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
	if (InteractiveObjectName.IsEmpty()) {
		UE_LOG(LogTemp, Warning, TEXT("No object to interact with"));
	}

	if (InteractiveObjectName.Equals("Lever")) {
		Lever->OnPlayerInteraction();
	}

	if (InteractiveObjectName.Equals("Teleport")) {
		Teleport->OnPlayerInteraction();
	}
}

void APlayerCharacter::SetPlayersHealth(HealthType Type, float Value)
{
	if (Type == HealthType::Heal && Health < 100) {
		Health += Value;

		if (Health > 100) {
			Health = 100.f;
		}
	}

	if (Type == HealthType::Damage) {
		Health -= Value;

		if (Health < 0) {
			Health = 0;
			PlayerDeath();
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
}

void APlayerCharacter::PlayerDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Died"));
}


void APlayerCharacter::ManageInteractionWidget(bool bShouldBeVisible)
{
	if (InteractionWidgetClass) {
		if (bShouldBeVisible) {
			InteractionWidget = CreateWidget<UUserWidget>(GetWorld(), InteractionWidgetClass);

			if (InteractionWidget)
			{
				InteractionWidget->AddToViewport();
			}
		}
		else {
			InteractionWidget->RemoveFromViewport();
		}
	}
}

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) {
		return;
	}

	// This actually get the instance of the classes, that is how this code actually works
	Lever = Cast<ALever>(OtherActor);
	Teleport = Cast<ATeleport>(OtherActor);

	if (Lever == nullptr && Teleport == nullptr) {
		return;
	}

	InteractiveObjectName = OtherActor->GetActorLabel();

	if (Lever || Teleport) {
		ManageInteractionWidget(true);
	}
}

void APlayerCharacter::OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Lever || Teleport) {
		ManageInteractionWidget(false);
		InteractiveObjectName.Empty();
	}
}

void APlayerCharacter::Animate()
{
	if (CanJump()) {
		if (bIsWalkingForwards) {
			if (!bIsRunning) {
				SpeedAnimation = 66.6f;
				DirectionAnimation = 50.f;
			}
			else {
				SpeedAnimation = 100.f;
				DirectionAnimation = 50.f;
			}
		}

		if (bIsWalkingBackwards) {
			SpeedAnimation = 0.f;
			DirectionAnimation = 50.f;
		}

		if (bIsWalkingRight) {
			DirectionAnimation = 100.f;
		}

		if (bIsWalkingLeft) {
			DirectionAnimation = 0.f;
		}
	}
	else {
		SpeedAnimation = 33.3f;
	}

	if (!bIsWalkingForwards && !bIsWalkingBackwards && !bIsWalkingRight && !bIsWalkingLeft) {
		SpeedAnimation = 33.3f;
	}
}

void APlayerCharacter::OnKeyDown(const FKey& Key) {
	if (Key == EKeys::W)
	{
		bIsWalkingForwards = true;
	}

	if (Key == EKeys::S)
	{
		bIsWalkingBackwards = true;
	}

	if (Key == EKeys::LeftShift) {
		bIsRunning = true;
	}

	if (Key == EKeys::A) {
		bIsWalkingRight = true;
	}

	if (Key == EKeys::D) {
		bIsWalkingLeft = true;
	}
}

void APlayerCharacter::OnKeyUp(const FKey& Key)
{
	if (Key == EKeys::W)
	{
		bIsWalkingForwards = false;
	}

	if (Key == EKeys::S)
	{
		bIsWalkingBackwards = false;
	}

	if (Key == EKeys::LeftShift) {
		bIsRunning = false;
	}

	if (Key == EKeys::A) {
		bIsWalkingRight = false;
	}

	if (Key == EKeys::D) {
		bIsWalkingLeft = false;
	}
}
