// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleshipsPlayerController.h"
#include "SelectableComponent.h"
#include "PlayerStartingPoint.h"
#include "WarshipFloatingPawnMovement.h"
#include "DrawDebugHelpers.h"

void ABattleshipsPlayerController::BeginPlay()
{
	Super::BeginPlay();
	FInputModeGameAndUI InputModeData;
	InputModeData.SetHideCursorDuringCapture(false);
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
	InputComponent->BindAction(TEXT("MouseClick"), EInputEvent::IE_Released, this, &ABattleshipsPlayerController::OnMouseRelease);
	InputComponent->BindAxis("MouseX", this, &ABattleshipsPlayerController::MouseX);
	InputComponent->BindAxis("MouseY", this, &ABattleshipsPlayerController::MouseY);
}

void ABattleshipsPlayerController::SetControlledPawn(FHitResult Hit)
{
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit == nullptr) return;

	UE_LOG(LogTemp, Warning, TEXT("Clicked: %s"), *ActorHit->GetName());

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
}

void ABattleshipsPlayerController::RotateShip()
{
	if (!ActivePawn) return;

	float Dist = FVector2D::Distance(InitialMousePosition, CurrentMousePosition);
	float PawnZ = ActivePawn->GetActorLocation().Z;

	FVector MouseDirection = FVector(CurrentMousePosition.X - InitialMousePosition.X, CurrentMousePosition.Y - InitialMousePosition.Y, PawnZ);
	FVector LineStart = ActivePawn->GetActorLocation();
	FVector LineEnd = LineStart + MouseDirection.GetSafeNormal() * 5.0f * Dist;
	LineStart.Z = PawnZ;
	LineEnd.Z = PawnZ;

	// Adjusting for the rotation of the player
	float AdjustmentDegrees = 0.0f;

	if (Startpoint)
	{
		AdjustmentDegrees = Startpoint->GetRotationAdjustment();
	}
	if (Dist > 10.f)
	{
		Rotation = FRotationMatrix::MakeFromX(LineEnd - LineStart).Rotator();
		Rotation.Yaw += AdjustmentDegrees;

		ActivePawn->SetActorRelativeRotation(Rotation);
	}
}

void ABattleshipsPlayerController::MoveShipForward()
{
	if (!ActivePawn) return;
	ActivePawn->TriggerMove(LaunchPower);
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
		if (!Ship) continue;
		USelectableComponent* SelectableComponent = Ship->FindComponentByClass<USelectableComponent>();
		SelectableComponent->DeselectActor();
	}
}

void ABattleshipsPlayerController::StartMouseDrag()
{
	bIsDragging = true;
	float X;
	float Y;
	GetMousePosition(X, Y);
	InitialMousePosition = FVector2D(X, Y);
}

void ABattleshipsPlayerController::StopMouseDrag()
{
	bIsDragging = false;

	if (!ActivePawn) return;

	if (bIsActionMoving)
	{
		RotateShip();
		MoveShipForward();

		//Set the values back to zero
		Rotation = FRotator::ZeroRotator;
		LaunchPower = 0.0f;
	}
}

void ABattleshipsPlayerController::GetMouseDrag()
{
	if (!ActivePawn) return;
	float X;
	float Y;
	GetMousePosition(X, Y);
	CurrentMousePosition = FVector2D(X, Y);

	float Dist = FVector2D::Distance(InitialMousePosition, CurrentMousePosition);
	if (Dist > MaxDist)
	{
		Dist = MaxDist;
	}
	LaunchPower = Dist / MaxDist;
}

void ABattleshipsPlayerController::OnMouseClick()
{
	FHitResult HitResultShip;
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, HitResultShip))
	{
		SetControlledPawn(HitResultShip);
		if (bIsActionMoving)
		{
			StartMouseDrag();
		}
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

void ABattleshipsPlayerController::OnMouseRelease()
{
	StopMouseDrag();
}

void ABattleshipsPlayerController::AbilityTrigger() {
	if (!ActivePawn) return;
	UseAbility(ActivePawn);
}

void ABattleshipsPlayerController::SwitchActionType()
{
	//true - Action = move
	//false - Action = attack
	bIsActionMoving = !bIsActionMoving;
	UE_LOG(LogTemp, Warning, TEXT("Switched the action type to %d"), bIsActionMoving);
}

void ABattleshipsPlayerController::MouseX(float Value)
{
	if (bIsDragging)
		GetMouseDrag();
}

void ABattleshipsPlayerController::MouseY(float Value)
{
	if (bIsDragging)
		GetMouseDrag();
}