// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BattleshipsPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MINIBATTLESHIPS_API ABattleshipsPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay();

private:
};
