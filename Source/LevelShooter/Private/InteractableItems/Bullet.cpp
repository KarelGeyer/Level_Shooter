#include "InteractableItems/Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Enemy/EnemyCharacter.h>
#include "Player/PlayerCharacter.h"


ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	RootComponent = BulletMesh;

	BulletMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovementComponent"));
	BulletMovementComponent->InitialSpeed = 10000;
	BulletMovementComponent->MaxSpeed = 20000;
}

void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != nullptr) {
		AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor);

		if (Enemy != nullptr) {
			Enemy->SetEnemyHealth(APlayerCharacter::Damage);
		}

		Destroy();
	}
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	BulletMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);

}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

