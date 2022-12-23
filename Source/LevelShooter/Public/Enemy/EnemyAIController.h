
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

class AEnemyCharacter;
class UCharacterMovementComponent;

UCLASS()
class LEVELSHOOTER_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI")
		FVector PatrolLocation;

private:
	APawn* PlayerPawn;
	FVector IntialPositon;
	AEnemyCharacter* EnemyCharacter;
	float MaxSpeed;

	UPROPERTY(EditAnywhere)
		UBehaviorTree* AIBehavior;

	void RunAndInitAI();
	void Chase();
};
