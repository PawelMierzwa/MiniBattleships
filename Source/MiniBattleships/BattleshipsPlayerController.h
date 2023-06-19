// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Warship.h"
#include "BattleshipsPlayerController.generated.h"

/**
 * 
 */
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

private:
	void SetControlledPawn(FHitResult HitResult);
	void UseAbility(AWarship* User);

	void OnShipSelected();
	void DeselectAllShips();

	//Input bindings
	void OnMouseClick();
	void OnMouseRelease();
	void AbilityTrigger();
	void SwitchActionType();

	// Defines if the action made is moving or attacking
	bool isActionMoving = 1;
	//Current clicked pawn
	AWarship* ActivePawn;
	TArray<AWarship*> PlayerShips;
};
