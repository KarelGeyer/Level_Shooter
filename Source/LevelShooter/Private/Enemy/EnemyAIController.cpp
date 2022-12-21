// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAIController.h"
#include <Kismet/GameplayStatics.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/EnemyCharacter.h"
#include <NavigationSystem.h>

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	PatrolLocation = GetRandomPoint();
	IntialPositon = GetPawn()->GetActorLocation();

	SetFocus(PlayerPawn);

	if (AIBehavior) {
		RunBehaviorTree(AIBehavior);
		GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolLocation"), PatrolLocation);
		GetBlackboardComponent()->SetValueAsVector(TEXT("InitialPosition"), IntialPositon);
	}
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Chase();
}

void AEnemyAIController::Chase()
{
	FVector Location = GetPawn()->GetActorLocation();
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	float DistanceToPlayer = FVector::Dist(Location, PlayerLocation);

	if (DistanceToPlayer < 1500 && LineOfSightTo(PlayerPawn)) {
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
	}
	else {
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}
}

FNavLocation AEnemyAIController::GetRandomPoint()
{
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	float Radius = 1500.0f;
	FNavLocation RandomLocation;
	bool bLocationFound = NavSys->GetRandomReachablePointInRadius(IntialPositon, Radius, RandomLocation);

	if (bLocationFound)
	{
		return RandomLocation;
	}
	else
	{
		return FNavLocation();
	}

}
