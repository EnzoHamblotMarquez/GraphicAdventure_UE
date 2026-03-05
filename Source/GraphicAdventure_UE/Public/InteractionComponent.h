// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractionDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAPHICADVENTURE_UE_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

	void OnInteraction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AActor* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction");
	AActor* NPC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction");
	AActor* Door;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction");
	float InteractionRadius = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction");
	float InteractionAngle = 60.f;

	void CheckInteractionRadius(AActor& interactable, AActor& player);
	void CheckInteractionCone(AActor& interactable, AActor& player);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// Blueprint-accessible Event Dispatcher
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FInteractionDelegate OnNpcInteraction;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FInteractionDelegate OnDoorInteraction;

	// Function to trigger the event
	UFUNCTION(BlueprintCallable, Category = "Events") //! //? In case someone wants to add an interaction through blueprints
	void TriggerInteraction(AActor* interactable);
		
};
