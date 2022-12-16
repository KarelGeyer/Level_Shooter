// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleport.generated.h"

class APlayerCharacter;
class UBoxComponent;

UCLASS()
class LEVELSHOOTER_API ATeleport : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATeleport();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	APlayerCharacter* Player;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UBoxComponent* InteractionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Teleport")
		FVector TeleportLocation;

	void OnPlayerInteraction();
};
