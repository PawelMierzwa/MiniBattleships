// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Warship.generated.h"

UCLASS()
class MINIBATTLESHIPS_API AWarship : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWarship();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Damage handling
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	// Returns if a pawn is dead
	UFUNCTION(BlueprintPure)
	bool bIsDead() const;

	// Sends current health state to blueprint UI
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	void TriggerMove(float Power);

private:
	// Hp set on start
	UPROPERTY(EditDefaultsOnly)
	int16 MaxHealthPoints = 3;
	int16 CurrentHealthPoints;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float PowerMultiplier = 500.0f;
	float LaunchPower = 0.0f;
	bool bIsLaunching = false;

	float LoopTimer = 0.0f;
	FTimerHandle MoveTimer;

	void UpdateMove();

	//Component responsible for showing and hiding the select decal
	UPROPERTY(VisibleAnywhere)
	class USelectableComponent* SelectableComponent;
	//Component handling the movement
	UPROPERTY(VisibleAnywhere)
	class UWarshipFloatingPawnMovement* MovementComponent;
	//Circle indicating which pawn is selected
	UPROPERTY(VisibleAnywhere)
	class UDecalComponent* DecalComponent;
	//Collision box
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;
	//Warships Static Mesh
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ShipMesh;
};
