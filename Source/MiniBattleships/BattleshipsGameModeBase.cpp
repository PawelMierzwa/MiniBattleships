// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleshipsGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "BattleshipsPlayerController.h"
#include "PlayerStartingPoint.h"
#include "Warship.h"
#include "PlayerCameraPawn.h"

ABattleshipsGameModeBase::ABattleshipsGameModeBase()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStartingPoint::StaticClass(), ActorPlayerSpawns);
}

void ABattleshipsGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	AActor* SelectedSpawn;
	int16 SpawnsCount = ActorPlayerSpawns.Num();
	SelectedSpawn = ActorPlayerSpawns[FMath::RandRange(0, SpawnsCount - 1)];

	if (!SelectedSpawn) return;

	APlayerCameraPawn* CameraPawn = nullptr;
	APlayerStartingPoint* SelectedStartingPoint = Cast<APlayerStartingPoint>(SelectedSpawn);

	if (SelectedStartingPoint)
	{
		const FVector CameraLocation = SelectedStartingPoint->GetCameraLocation();
		const FRotator CameraRotation = SelectedStartingPoint->GetCameraRotation();

		FActorSpawnParameters Params;
		Params.bNoFail = true;
		Params.OverrideLevel = GetLevel();

		CameraPawn = GetWorld()->SpawnActor<APlayerCameraPawn>(APlayerCameraPawn::StaticClass(), CameraLocation, CameraRotation, Params);
	}
	if (CameraPawn != nullptr)
	{
		ABattleshipsPlayerController* BattleshipsNewPlayer = Cast<ABattleshipsPlayerController>(NewPlayer);
		BattleshipsNewPlayer->SetPlayerStartingPoint(SelectedStartingPoint);
		NewPlayer->Possess(CameraPawn);
		SpawnShips(BattleshipsNewPlayer, SelectedStartingPoint);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CAMERA CANT BE POSSESSED"));
	}

	ActorPlayerSpawns.RemoveSingle(SelectedSpawn);
}

void ABattleshipsGameModeBase::SpawnShips(ABattleshipsPlayerController* Controller, APlayerStartingPoint* StartingPoint)
{
	FActorSpawnParameters Params;
	Params.bNoFail = true;

	for (size_t i = 0; i < 4; i++)
	{
		if (StartingPoint)
		{
			AWarship* Ship = GetWorld()->SpawnActor<AWarship>(
				WarshipTestPawnBP,
				StartingPoint->GetShipSpawnLocation(i),
				StartingPoint->GetShipSpawnRotation(i),
				Params);
			Ship->SetPlayerController(Controller);
			Controller->AddPlayerShip(Ship);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("CANNOT ACCESS SHIPS #%i SPAWNPOINT"), i);
		}
	}
}