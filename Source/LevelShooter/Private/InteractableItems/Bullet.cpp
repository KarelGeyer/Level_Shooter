// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableItems/Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	RootComponent = BulletMesh;

	BulletMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovementComponent"));
	BulletMovementComponent->InitialSpeed = 10000;
	BulletMovementComponent->MaxSpeed = 20000;
}

void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// print Other actors name
	if (OtherActor != nullptr) {

		Destroy();
	}
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	BulletMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);

}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

