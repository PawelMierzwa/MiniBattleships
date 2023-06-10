// Fill out your copyright notice in the Description page of Project Settings.


#include "Warship.h"

// Sets default values
AWarship::AWarship()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWarship::BeginPlay()
{
	Super::BeginPlay();
	
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
	UE_LOG(LogTemp, Warning, TEXT("Switched the action type to %b"), isActionMoving);
}

