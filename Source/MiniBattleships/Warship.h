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

	// Sends current health state to blueprint UI
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	void SetPlayerController(class ABattleshipsPlayerController* Player) { BattleshipsPlayerController = Player; };
	class ABattleshipsPlayerController* GetShipPlayerController() { return BattleshipsPlayerController; };

	void TriggerMove(float Power);
	void TriggerFire(FRotator& Direction);

	void HandleDestruction();

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

	class ABattleshipsPlayerController* BattleshipsPlayerController;
	const class ABattleshipsGameModeBase* BattleshipsGameMode;

	UFUNCTION()
	void UpdateMove();

	UFUNCTION()
	void DamageTaken(
		AActor* DamagedActor, 
		float Damage, 
		const UDamageType* DamageType, 
		class AController* Instigatr, 
		AActor* DamageCauser);

	UFUNCTION()
	bool bIsDead() const;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;

	//Component responsible for showing and hiding the select decal
	UPROPERTY(VisibleAnywhere)
	class USelectableComponent* SelectableComponent;

	//Circle indicating which pawn is selected
	UPROPERTY(VisibleAnywhere)
	class UDecalComponent* DecalComponent;

	UPROPERTY(VisibleAnywhere)
	class UWarshipFloatingPawnMovement* MovementComponent;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ShipMesh;
	
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* ProjectileSpawnpoint;
};
