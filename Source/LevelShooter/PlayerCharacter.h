// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class LEVELSHOOTER_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		float SpeedAnimation = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		float DirectionAnimation = 0.f;

private:
	// UProperties
	UPROPERTY(EditInstanceOnly, Category = "Movement")
		float Speed = 180.f;

	UFUNCTION(BlueprintCallable, Category = "Animation")
		void OnKeyDown(const FKey& Key);

	UFUNCTION(BlueprintCallable, Category = "Animation")
		void OnKeyUp(const FKey& Key);

	bool IsWalkingForwards = false;
	bool IsWalkingBackwards = false;
	bool IsJumping = false;
	bool IsRunning = false;

	// Methods
	void Move(float Value);
	void Rotate(float Value);
	void Run();
	void StopRunning();
	void Animate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
