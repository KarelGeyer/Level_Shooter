// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 *
 */
UCLASS()
class LEVELSHOOTER_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	APawn* PlayerPawn;
	FVector PatrolLocation;
	FVector IntialPositon;

	UPROPERTY(EditAnywhere)
		UBehaviorTree* AIBehavior;

	void Chase();
	FNavLocation GetRandomPoint();
};
