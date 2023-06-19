// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectableComponent.generated.h"

class UMaterialInstance;
class UMaterialInstanceDynamic;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINIBATTLESHIPS_API USelectableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USelectableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)	
	void SelectActor();
	UFUNCTION(BlueprintCallable)
	void DeselectActor();
	UFUNCTION(BlueprintCallable)
	void HoverActor();
	UFUNCTION(BlueprintCallable)
	void UnhoverActor();

private:
	float GetOwnerCollisionSize();
	float GetOwnerCollisionHeight();

	bool bSelected = false;
	bool bHovered = false;

	UPROPERTY()
	UDecalComponent* DecalComponent;
};
