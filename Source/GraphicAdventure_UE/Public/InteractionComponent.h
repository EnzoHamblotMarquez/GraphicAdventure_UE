// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdventureCharacter.h"
#include "InteractionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAPHICADVENTURE_UE_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AAdventureCharacter* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction");
	AActor* NPC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction");
	float InteractionRadius = 10.f;

	void CheckInteractionRadius(AActor& interactable, AActor& player);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
