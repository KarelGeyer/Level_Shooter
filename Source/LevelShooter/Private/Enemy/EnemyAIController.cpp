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

	if (EnemyCharacter->IsDead)
	{
		// ClearFocus(2);
		StopMovement();
	}
	else {
		Chase();
	}

}

void AEnemyAIController::RunAndInitAI()
{
	if (AIBehavior) {
		RunBehaviorTree(AIBehavior);

		EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());

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
	if (EnemyCharacter->GetDistanceToPlayer() < 1500 && LineOfSightTo(PlayerPawn)) {
		EnemyCharacter->ManageAnimation(100.f, true, false, 500.f);

		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
		SetFocus(PlayerPawn);

		if (EnemyCharacter->GetDistanceToPlayer() < 150) {
			EnemyCharacter->ManageAnimation(25.f, true, true);
		}
	}
	else {
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
		if (EnemyCharacter->IsMoving()) {
			EnemyCharacter->ManageAnimation(50.f);
		}
		else {
			EnemyCharacter->ManageAnimation(25.f);
		}
	}
}
