// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAIController.h"
#include <Kismet/GameplayStatics.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/EnemyCharacter.h"
#include <NavigationSystem.h>
#include "Enemy/EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	RunAndInitAI();
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Chase();
	Attack();;
}

void AEnemyAIController::RunAndInitAI()
{
	if (AIBehavior) {
		RunBehaviorTree(AIBehavior);

		EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
		MovementComp = EnemyCharacter->GetCharacterMovement();

		if (EnemyCharacter)
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolLocation"), EnemyCharacter->PatrolLocation);
		}

		GetBlackboardComponent()->SetValueAsVector(TEXT("InitialPosition"), GetPawn()->GetActorLocation());
		GetBlackboardComponent()->SetValueAsBool(TEXT("IsAttacking"), false);
	}
}

void AEnemyAIController::Chase()
{
	if (GetDistanceToPlayer() < 1500 && LineOfSightTo(PlayerPawn)) {
		SetFocus(PlayerPawn);

		MovementComp->MaxWalkSpeed = 400.f;

		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
	}
	else {
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
		MovementComp->MaxWalkSpeed = 200.f;
	}
}

void AEnemyAIController::Attack()
{
	GetBlackboardComponent()->SetValueAsBool(TEXT("IsAttacking"), GetDistanceToPlayer() < 150);
}

float AEnemyAIController::GetDistanceToPlayer()
{
	FVector Location = GetPawn()->GetActorLocation();
	FVector PlayerLocation = PlayerPawn->GetActorLocation();

	return FVector::Dist(Location, PlayerLocation);
}
