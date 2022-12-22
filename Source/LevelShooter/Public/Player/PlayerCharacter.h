// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;
class IInteractionInterface;
class UUserWidget;
class ATeleport;
class ALever;

enum class HealthType {
	Heal,
	Damage
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		float Health = 100.f;

	void SetPlayersHealth(HealthType Type, float Value);

private:
	// UProperties
	UPROPERTY(EditInstanceOnly, Category = "Movement")
		float Speed = 180.f;

	UPROPERTY(EditAnywhere)
		UBoxComponent* InteractionBox;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> InteractionWidgetClass;

	UFUNCTION(BlueprintCallable, Category = "Animation")
		void OnKeyDown(const FKey& Key);

	UFUNCTION(BlueprintCallable, Category = "Animation")
		void OnKeyUp(const FKey& Key);

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	ALever* Lever;
	ATeleport* Teleport;
	UUserWidget* InteractionWidget;
	FString InteractiveObjectName;

	bool bIsWalkingForwards = false;
	bool bIsWalkingBackwards = false;
	bool bIsJumping = false;
	bool bIsRunning = false;

	// Methods
	void Move(float Value);
	void Rotate(float Value);
	void Run();
	void StopRunning();
	void Animate();
	void ManageInteractionWidget(bool bShouldBeVisible);
	bool RayCastTrace(FHitResult& Hit, FVector& ShotDirection);
	void Interact();
	void PlayerDeath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
