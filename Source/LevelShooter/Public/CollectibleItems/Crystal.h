// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Crystal.generated.h"

class UParticleSystem;

UCLASS()
class LEVELSHOOTER_API ACrystal : public AActor
{
	GENERATED_BODY()

public:
	ACrystal();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* Mesh;

private:
	//Particle system
	UPROPERTY(EditAnywhere, Category = "Particles")
		UParticleSystem* PickedUpEffect;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
