// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lever.generated.h"


class UUserWidget;
class APlayerCharacter;
class ALiftPlartform;

UCLASS()
class LEVELSHOOTER_API ALever : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALever();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* HandleMesh;

	void OnPlayerInteraction();

private:
	TArray<AActor*> Children;

	bool IsPulled = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
