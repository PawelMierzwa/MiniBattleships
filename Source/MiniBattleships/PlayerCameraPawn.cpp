// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCameraPawn.h"

// Sets default values
APlayerCameraPawn::APlayerCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = SceneComponent;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	CameraComponent->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void APlayerCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

