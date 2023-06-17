// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStartingPoint.h"


// Sets default values
APlayerStartingPoint::APlayerStartingPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = SceneComponent;

	CameraLocation = CreateDefaultSubobject<UBoxComponent>(TEXT("Camera location"));
	CameraLocation->SetupAttachment(SceneComponent);

	ShipSpawnpoint1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Ship Spawnpoint 1"));
	ShipSpawnpoint1->SetupAttachment(SceneComponent);

	ShipSpawnpoint2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Ship Spawnpoint 2"));
	ShipSpawnpoint2->SetupAttachment(SceneComponent);

	ShipSpawnpoint3 = CreateDefaultSubobject<UBoxComponent>(TEXT("Ship Spawnpoint 3"));
	ShipSpawnpoint3->SetupAttachment(SceneComponent);

	ShipSpawnpoint4 = CreateDefaultSubobject<UBoxComponent>(TEXT("Ship Spawnpoint 4"));
	ShipSpawnpoint4->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void APlayerStartingPoint::BeginPlay()
{
	Super::BeginPlay();
	
}
