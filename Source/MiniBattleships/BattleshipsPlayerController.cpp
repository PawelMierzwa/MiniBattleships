// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleshipsPlayerController.h"
#include "SelectableComponent.h"
#include "DrawDebugHelpers.h"

void ABattleshipsPlayerController::BeginPlay()
{
	Super::BeginPlay();
	FInputModeGameAndUI InputModeData;
	SetInputMode(InputModeData);
	bShowMouseCursor = true;
}

void ABattleshipsPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABattleshipsPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("Ability"), EInputEvent::IE_Pressed, this, &ABattleshipsPlayerController::AbilityTrigger);
	InputComponent->BindAction(TEXT("MoveAttackSwitch"), EInputEvent::IE_Pressed, this, &ABattleshipsPlayerController::SwitchActionType);
	InputComponent->BindAction(TEXT("MouseClick"), EInputEvent::IE_Pressed, this, &ABattleshipsPlayerController::OnMouseClick);
}

void ABattleshipsPlayerController::SetControlledPawn(FHitResult Hit)
{
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit == nullptr) return;


	UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *ActorHit->GetName());
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Hit: %s"), *ActorHit->GetName()));

	AWarship* ClickedPawn = Cast<AWarship>(ActorHit);
	if (PlayerShips.Find(ClickedPawn) != INDEX_NONE)
	{
		ActivePawn = ClickedPawn;
	OnShipSelected();
}
}

void ABattleshipsPlayerController::UseAbility(AWarship* User)
{
	if (User == nullptr) return;
	UE_LOG(LogTemp, Warning, TEXT("%s has used an ability!"), *User->GetName());
	//Actor component of a specific ability :)
}

void ABattleshipsPlayerController::OnShipSelected()
{
	DeselectAllShips();
	USelectableComponent* SelectableComponent = ActivePawn->FindComponentByClass<USelectableComponent>();
	SelectableComponent->SelectActor();
}

void ABattleshipsPlayerController::DeselectAllShips()
{
	for (AWarship* Ship : PlayerShips)
	{
		USelectableComponent* SelectableComponent = Ship->FindComponentByClass<USelectableComponent>();
		SelectableComponent->DeselectActor();
	}
}

void ABattleshipsPlayerController::OnMouseClick()
{
	FHitResult HitResultShip;
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, HitResultShip))
	{
		SetControlledPawn(HitResultShip);
		return;
	}

	FHitResult HitResultFloor;
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel2, false, HitResultFloor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Clicked on the floor, deselecting.."));
		ActivePawn = nullptr;
		DeselectAllShips();
		return;
	}
}

void ABattleshipsPlayerController::AbilityTrigger() {
	if (ActivePawn == nullptr) return;
	UseAbility(ActivePawn);
}

void ABattleshipsPlayerController::SwitchActionType()
{
	//true - Action = move
	//false - Action = attack
	isActionMoving = !isActionMoving;
	UE_LOG(LogTemp, Warning, TEXT("Switched the action type to %d"), isActionMoving);
}
