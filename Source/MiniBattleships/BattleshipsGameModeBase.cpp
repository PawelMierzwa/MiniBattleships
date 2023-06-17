// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleshipsGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerStartingPoint.h"
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
	UE_LOG(LogTemp, Warning, TEXT("Found a spawn: %s"), *SelectedSpawn->GetName());

	APlayerCameraPawn* CameraPawn = nullptr;
	APlayerStartingPoint* SelectedStartingPoint = Cast<APlayerStartingPoint>(SelectedSpawn);

	if (SelectedStartingPoint)
	{
		const FVector CameraLocation = SelectedStartingPoint->GetCameraLocation();
		const FRotator CameraRotation = SelectedStartingPoint->GetCameraRotation();
		UE_LOG(LogTemp, Warning, TEXT("CAMERA LOCATION: X: %d Y: %d Z: %d"), CameraLocation.X, CameraLocation.Y, CameraLocation.Z);

		FActorSpawnParameters Params;
		Params.bNoFail = true;
		Params.OverrideLevel = GetLevel();

		CameraPawn = GetWorld()->SpawnActor<APlayerCameraPawn>(APlayerCameraPawn::StaticClass(), CameraLocation, CameraRotation, Params);
	}
	if (CameraPawn != nullptr)
	{
		NewPlayer->Possess(CameraPawn);
		UE_LOG(LogTemp, Warning, TEXT("CAMERA POSSESSED: %s"), *CameraPawn->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CAMERA CANT BE POSSESSED"));
	}

	ActorPlayerSpawns.RemoveSingle(SelectedSpawn);
}

