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
class ABullet;

enum class HealthType {
	Heal,
	Damage
};

UCLASS()
class LEVELSHOOTER_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	static const int32 Damage = 25;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		float SpeedAnimation = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		float DirectionAnimation = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		USkeletalMeshComponent* WeaponComponent;

	UFUNCTION(BlueprintPure, Category = "HUD")
		float GetHealtBarValue() const;

	UFUNCTION(BlueprintPure, Category = "HUD")
		int32 GetCollectedCrystals() const;

	void SetPlayersHealth(HealthType Type, float Value);
	void SetCollectedCrystals();
	void SetHealth(float Value);

private:
	int32 CollectedCrystals = 0;

	UPROPERTY(EditInstanceOnly, Category = "Movement")
		float Speed = 180.f;

	UPROPERTY(EditAnywhere)
		UBoxComponent* InteractionBox;

	UPROPERTY(EditAnywhere)
		USceneComponent* BulletSpawnPoint;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> InteractionWidgetClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> PlayerHUDClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
		TSubclassOf<ABullet> BulletClass;

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
	UUserWidget* PlayerHUD;
	FString InteractiveObjectName;


	bool bIsWalkingForwards = false;
	bool bIsWalkingBackwards = false;
	bool bIsWalkingRight = false;
	bool bIsWalkingLeft = false;
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
	void Shoot();
	void SetupHUD();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
