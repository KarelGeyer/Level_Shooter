// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class APlayerCharacter;
class UCharacterMovementComponent;

UCLASS()
class LEVELSHOOTER_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		float EnemySpeedAnimation = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		float EnemyAngleAnimation = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		bool IsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		float AttackAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		float AttackSide;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI")
		FVector PatrolLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		USkeletalMeshComponent* WeaponComponent;

	bool IsMoving();
	float GetDistanceToPlayer();
	void ManageAnimation(float EnemySpeedAnimationSetter, bool bIsWeaponVisibleSetter = false, bool bIsAttackingSetter = false, float MovementSpeedSetter = 130.f);

private:
	APlayerCharacter* Player;
	FTimerHandle TimerHandle;
	UCharacterMovementComponent* MovementComp;

	void ManageAttackAnimation();
	void ManageRotation();

	UFUNCTION()
		void OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
