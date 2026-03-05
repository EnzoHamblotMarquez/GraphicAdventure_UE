// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<AActor>(GetOwner());
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UInteractionComponent::OnInteraction()
{
	CheckInteractionRadius(*NPC, *Owner);
}

void UInteractionComponent::CheckInteractionRadius(AActor& interactable, AActor& player)
{
	float Distance = (interactable.GetActorLocation() - player.GetActorLocation()).Size();
	//UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), Distance);

	if (Distance < InteractionRadius)
	{
		CheckInteractionCone(interactable, player);
	}
}
void UInteractionComponent::CheckInteractionCone(AActor& interactable, AActor& player)
{
	FVector Direction = (interactable.GetActorLocation() - player.GetActorLocation()).GetSafeNormal();
	FVector PlayerForward = player.GetActorForwardVector();


	float dot = Direction | PlayerForward;
	float cosValue = FMath::Cos(FMath::DegreesToRadians(InteractionAngle / 2));

	//UE_LOG(LogTemp, Warning, TEXT("AngleCos: %f, CosValue: %f"), dot, cosValue);
	if (dot > cosValue)
	{
		AActor* ptr = &interactable;
		TriggerInteraction(ptr);
	}
	
}

void UInteractionComponent::TriggerInteraction(AActor* interactable)
{
	if (interactable == NPC)
	{
		OnNpcInteraction.Broadcast();
		//UE_LOG(LogTemp, Warning, TEXT("Event"));
	}

	if (interactable == Door)
	{
		OnDoorInteraction.Broadcast();
		//UE_LOG(LogTemp, Warning, TEXT("Event"));
	}
}


