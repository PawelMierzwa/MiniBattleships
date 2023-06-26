// Fill out your copyright notice in the Description page of Project Settings.


#include "Warship.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "Components/BoxComponent.h"
#include "BattleshipsPlayerController.h"
#include "WarshipFloatingPawnMovement.h"
#include "SelectableComponent.h"
#include "Projectile.h"


AWarship::AWarship()
{
	PrimaryActorTick.bCanEverTick = true;

	//Root component
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	RootComponent = BoxCollision;
	BoxCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Warship Mesh"));
	ShipMesh->SetupAttachment(BoxCollision);

	ProjectileSpawnpoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawnpoint"));
	ProjectileSpawnpoint->SetupAttachment(BoxCollision);

	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("Selection Decal Component"));
	DecalComponent->AttachToComponent(BoxCollision, FAttachmentTransformRules::KeepRelativeTransform);

	// Custom components
	MovementComponent = CreateDefaultSubobject<UWarshipFloatingPawnMovement>(TEXT("Movement Component"));
	SelectableComponent = CreateDefaultSubobject<USelectableComponent>(TEXT("Selectable Component"));
}

void AWarship::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealthPoints = MaxHealthPoints;
	OnTakeAnyDamage.AddDynamic(this, &AWarship::DamageTaken);
}

void AWarship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AWarship::bIsDead() const
{
	return CurrentHealthPoints <= 0;
}

float AWarship::GetHealthPercent() const
{
	return CurrentHealthPoints / MaxHealthPoints;
}

void AWarship::TriggerMove(float Power)
{
	if (!bIsLaunching)
	{
		if (!GetVelocity().IsZero()) return;
		bIsLaunching = true;
		LoopTimer = 0.0f;
		LaunchPower = Power;
		GetWorldTimerManager().ClearTimer(MoveTimer);
		GetWorldTimerManager().SetTimer(MoveTimer, this, &AWarship::UpdateMove, 0.05f, true);
	}
}

void AWarship::TriggerFire(FRotator& Direction)
{
	FVector Location = ProjectileSpawnpoint->GetComponentLocation();

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Direction);
	Projectile->SetOwner(this);
}

void AWarship::HandleDestruction()
{
	SelectableComponent->DeselectActor();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void AWarship::UpdateMove()
{
	if (bIsLaunching)
	{
		FVector Velocity;
		LoopTimer += 0.05f;
		
		if (LoopTimer <= 0.5)
		{
			Velocity = GetActorForwardVector() * PowerMultiplier * LaunchPower;
		}
		else
		{
			if (LoopTimer >= 2.5f || Velocity.IsNearlyZero())
			{
				GetWorldTimerManager().ClearTimer(MoveTimer);
				LoopTimer = 0.0f;
				bIsLaunching = false;
				return;
			}
			Velocity = Velocity / 1.5;
		}
		FHitResult HitResult;
		AddActorWorldOffset(Velocity, true, &HitResult);
		if (HitResult.bBlockingHit)
		{
			Velocity = FVector::ZeroVector;
		}
	}
}

void AWarship::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigatr, AActor* DamageCauser) {
	if (Damage <= 0.f) return;

	CurrentHealthPoints -= Damage;
	if (bIsDead())
	{
		HandleDestruction();
		BattleshipsPlayerController->RemovePlayerShip(this);
		DetachFromControllerPendingDestroy();
		ShipMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
