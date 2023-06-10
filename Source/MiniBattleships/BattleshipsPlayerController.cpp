// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleshipsPlayerController.h"

void ABattleshipsPlayerController::BeginPlay()
{
	FInputModeGameOnly InputModeData;
	SetInputMode(InputModeData);
	bShowMouseCursor = true;
}
