// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PlayerStartingPoint.generated.h"

UCLASS()
class MINIBATTLESHIPS_API APlayerStartingPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerStartingPoint();

public:
	FVector GetCameraLocation() { return CameraLocation->GetComponentLocation(); };
	FRotator GetCameraRotation() { return CameraLocation->GetComponentRotation(); };
	FVector GetShipSpawnLocation(int16 index);
	FRotator GetShipSpawnRotation(int16 index);

private:
	TArray<UBoxComponent*> SpawnArray;

	UPROPERTY()
	USceneComponent* SceneComponent;
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* CameraLocation;
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* ShipSpawnpoint1;
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* ShipSpawnpoint2;
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* ShipSpawnpoint3;
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* ShipSpawnpoint4;
};
