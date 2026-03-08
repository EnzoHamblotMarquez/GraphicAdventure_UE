#include "InteractionComponent.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<AActor>(GetOwner());

}


void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckInteractionRange(*NPC, *Owner);
	CheckInteractionRange(*Door, *Owner);

}

void UInteractionComponent::OnInteraction()
{
	CheckInteractionRadius(*NPC, *Owner);
	CheckInteractionRadius(*Door, *Owner);
}

void UInteractionComponent::CheckInteractionRadius(AActor& interactable, AActor& player)
{
	float Distance = (interactable.GetActorLocation() - player.GetActorLocation()).Size();

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
	}

	if (interactable == Door)
	{
		OnDoorInteraction.Broadcast();
	}
}

void UInteractionComponent::CheckInteractionRange(AActor& interactable, AActor& player)
{
	float Distance = (interactable.GetActorLocation() - player.GetActorLocation()).Size();

	if (Distance >= InteractionRadius)
	{
		AwayFromInteractable.Broadcast();
	}
	else
	{
		CloseToInteractable.Broadcast();
	}
}



