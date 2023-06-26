// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Warship.h"
#include "BattleshipsPlayerController.generated.h"


UCLASS()
class MINIBATTLESHIPS_API ABattleshipsPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

public:
	void AddPlayerShip(AWarship* ShipToAdd) { PlayerShips.Add(ShipToAdd); };
	void RemovePlayerShip(AWarship* ShipToRemove);
	void SetPlayerStartingPoint(class APlayerStartingPoint* StartingPoint) { Startpoint = StartingPoint; };

private:
	void SetControlledPawn(FHitResult HitResult);
	void UseAbility(AWarship* User);

	//Pawn movement
	void RotateShip();
	void MoveShipForward();

	//Selecting/Deselecting
	void OnShipSelected();
	void DeselectAllShips();

	//Mouse Drag Handling
	void StartMouseDrag();
	void StopMouseDrag();
	void GetMouseDrag();

	//Input Action bindings
	void OnMouseClick();
	void OnMouseRelease();
	void AbilityTrigger();
	void SwitchActionType();

	//Input Axis bindings
	void MouseX(float Value);
	void MouseY(float Value);

	FVector2D InitialMousePosition;
	FVector2D CurrentMousePosition;
	bool bIsDragging = false;

	FRotator Rotation = FRotator::ZeroRotator;
	float LaunchPower = 0.0f;
	// Defines if the action made is moving or attacking
	bool bIsActionMoving = 1;

	UPROPERTY(EditDefaultsOnly)
	float MaxDist = 100.0;

	AWarship* ActivePawn;

	//Array of pawns that belong to the player
	TArray<AWarship*> PlayerShips;

	class APlayerStartingPoint* Startpoint;
};
