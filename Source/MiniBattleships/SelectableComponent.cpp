// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectableComponent.h"
#include "Components/DecalComponent.h"
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
USelectableComponent::USelectableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void USelectableComponent::BeginPlay()
{
	Super::BeginPlay();

	float DecalHeight = GetOwnerCollisionHeight();
	float DecalRadius = GetOwnerCollisionSize() / 2;

	DecalComponent = GetOwner()->FindComponentByClass<UDecalComponent>();

	//Decal rotation and size
	DecalComponent->SetRelativeRotation(FRotator::MakeFromEuler(FVector(0.0f, -90.0f, 0.0f)));
	DecalComponent->DecalSize = FVector(DecalHeight, DecalRadius, DecalRadius);

	DecalComponent->SetHiddenInGame(true);
}


// Called every frame
void USelectableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USelectableComponent::SelectActor()
{
	if (bSelected) return;

	bSelected = true;

	// Update selection circle.
	if (IsValid(DecalComponent))
	{
		DecalComponent->SetHiddenInGame(false);
	}
}

void USelectableComponent::DeselectActor()
{
	if (!bSelected) return;

	bSelected = false;

	// Update selection circles.
	if (IsValid(DecalComponent))
	{
		DecalComponent->SetHiddenInGame(true);
	}
}

void USelectableComponent::HoverActor()
{

}

void USelectableComponent::UnhoverActor()
{

}

float USelectableComponent::GetOwnerCollisionSize()
{
	UBoxComponent* BoxComponent = GetOwner()->FindComponentByClass<UBoxComponent>();
	if (!IsValid(BoxComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find collision box for %s"), *GetOwner()->GetName());
		return 0.0f;
	}

	FCollisionShape CollisionShape = BoxComponent->GetCollisionShape();
	return FMath::Max(CollisionShape.Box.HalfExtentX, CollisionShape.Box.HalfExtentY) * 2;
}

float USelectableComponent::GetOwnerCollisionHeight()
{
	UBoxComponent* BoxComponent = GetOwner()->FindComponentByClass<UBoxComponent>();
	if (!IsValid(BoxComponent)) 
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find collision box for %s"), *GetOwner()->GetName());
		return 0.0f;
	}

	FCollisionShape CollisionShape = BoxComponent->GetCollisionShape();
	return CollisionShape.Box.HalfExtentZ * 2;
}
