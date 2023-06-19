// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleshipsGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MINIBATTLESHIPS_API ABattleshipsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ABattleshipsGameModeBase();

	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	TArray<AActor*> ActorPlayerSpawns;
	void SpawnShips(class ABattleshipsPlayerController* PlayerController, class APlayerStartingPoint* StartingPoint);

	UPROPERTY(EditDefaultsOnly, Category = "Warship")
	TSubclassOf<class AWarship> WarshipTestPawnBP;
};
