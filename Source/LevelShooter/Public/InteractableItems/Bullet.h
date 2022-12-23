// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class UProjectileMovementComponent;

UCLASS()
class LEVELSHOOTER_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		UStaticMeshComponent* BulletMesh;

private:

	UPROPERTY(EditAnywhere, Category = "Weapon")
		UProjectileMovementComponent* BulletMovementComponent;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
