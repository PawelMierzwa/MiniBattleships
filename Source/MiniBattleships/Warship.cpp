// Fill out your copyright notice in the Description page of Project Settings.


#include "Warship.h"
#include "BattleshipsGameModeBase.h"

// Sets default values
AWarship::AWarship()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root component setup
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	RootComponent = BoxCollision;
	BoxCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

	//Mesh setup
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Warship Mesh"));
	ShipMesh->SetupAttachment(BoxCollision);

	//Components setup
	MovementComponent = CreateDefaultSubobject<UWarshipMovementComponent>(TEXT("Movement Component"));
	SelectableComponent = CreateDefaultSubobject<USelectableComponent>(TEXT("Selectable Component"));
	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("Selection Decal Component"));
	DecalComponent->AttachToComponent(BoxCollision, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AWarship::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealthPoints = MaxHealthPoints;
}

// Called every frame
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
	//TODO: figure out the best way to display current hp on a pawn
	return CurrentHealthPoints/MaxHealthPoints;
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