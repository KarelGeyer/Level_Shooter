// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LiftPlartform.generated.h"

class ALiftPlartform;

UCLASS()
class LEVELSHOOTER_API ALiftPlartform : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALiftPlartform();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* BaseMesh;

	void ManageLift(bool bUp);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
