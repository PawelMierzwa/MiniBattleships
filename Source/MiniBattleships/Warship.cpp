// Fill out your copyright notice in the Description page of Project Settings.


#include "Warship.h"
#include "BattleshipsGameModeBase.h"

// Sets default values
AWarship::AWarship()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UWarshipMovementComponent>(TEXT("Movement Component"));

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

// Called to bind functionality to input
void AWarship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Ability"), EInputEvent::IE_Pressed, this, &AWarship::UseAbility);
	PlayerInputComponent->BindAction(TEXT("MoveAttackSwitch"), EInputEvent::IE_Pressed, this, &AWarship::SwitchActionType);

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

void AWarship::UseAbility()
{
	UE_LOG(LogTemp, Warning, TEXT("Ability used"));
	//Actor component of a specific ability :)
}

void AWarship::SwitchActionType()
{
	//true - Action = move
	//false - Action = attack
	isActionMoving = !isActionMoving;
	UE_LOG(LogTemp, Warning, TEXT("Switched the action type to %d"), isActionMoving);
}
