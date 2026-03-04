// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputActionValue.h"
#include "InteractionComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AdventureCharacter.generated.h"

UCLASS()
class GRAPHICADVENTURE_UE_API AAdventureCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAdventureCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Default Player Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input");
	class UInputMappingContext* PlayerMappingContext;

	//Move Function
	void Move(const FInputActionValue& value);

	//Interact Function 
	void Interact();
	UInteractionComponent* Interaction;

	//Input Actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input");
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input");
	class UInputAction* InteractAction;

	//Camera
	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	USpringArmComponent* SpringArm;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
