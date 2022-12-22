#include "Enemy/EnemyCharacter.h"
#include "Player/PlayerCharacter.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
#include "GameFramework/CharacterMovementComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Skeleton = GetMesh();
	WeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponComponent"));
	WeaponComponent->AttachToComponent(Skeleton, FAttachmentTransformRules::KeepWorldTransform, TEXT("Weapon_Socket"));
	MovementComp = GetCharacterMovement();
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	WeaponComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnWeaponOverlap);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyCharacter::ManageAttackAnimation, 2.2f, true);
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ManageAnimation();
	ManageRotation();
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
		IsAttacking = false;
	}

	if (!IsMoving() && GetDistanceToPlayer() < 150) {
		IsAttacking = true;
		EnemySpeedAnimation = 25;
	}

	if (!IsMoving() && GetDistanceToPlayer() > 150) {
		IsAttacking = false;
		EnemySpeedAnimation = 25;
	}

	EnemyAngleAnimation = 50;
	WeaponComponent->SetVisibility(IsMoving() || GetDistanceToPlayer() < 150 || IsAttacking);
}

void AEnemyCharacter::OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) {
		return;
	}

	Player = Cast<APlayerCharacter>(OtherActor);

	if (Player != nullptr) {
		Player->SetPlayersHealth(HealthType::Damage, 10.f);
	}
}

float AEnemyCharacter::GetDistanceToPlayer()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector Location = GetActorLocation();

	return FVector::Dist(Location, PlayerLocation);
}

void AEnemyCharacter::ManageAttackAnimation()
{
	if (IsAttacking) {
		AttackAngle = FMath::FRand();
		AttackSide = FMath::FRand();
	}
}

void AEnemyCharacter::ManageRotation()
{
	if (IsMoving()) {
		FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetActorLocation() + GetVelocity());
		SetActorRotation(NewRotation);
	}
}

