// Fill out your copyright notice in the Description page of Project Settings.


#include "Warship.h"
#include "BattleshipsGameModeBase.h"
#include "Components/DecalComponent.h"
#include "Components/BoxComponent.h"
#include "WarshipFloatingPawnMovement.h"
#include "SelectableComponent.h"


AWarship::AWarship()
{
	PrimaryActorTick.bCanEverTick = true;

	//Root component
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	RootComponent = BoxCollision;
	BoxCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

	//Mesh
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Warship Mesh"));
	ShipMesh->SetupAttachment(BoxCollision);

	//Selection decal
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
		bIsLaunching = true;
		LoopTimer = 0.0f;
		LaunchPower = Power;
		GetWorldTimerManager().ClearTimer(MoveTimer);
		GetWorldTimerManager().SetTimer(MoveTimer, this, &AWarship::UpdateMove, 0.05f, true);
	}
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

float AWarship::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (bIsDead())
	{
		ABattleshipsGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ABattleshipsGameModeBase>();
		if (GameMode != nullptr)
		{
			// TODO: Handle Pawn Death
			//GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();

		//TODO: Add Collision
		//GetCapsuleComponent()->SetCollsionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageApplied;
}