// Fill out your copyright notice in the Description page of Project Settings.


#include "AdventureCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"

#include "GameFramework/CharacterMovementComponent.h" //!


// Sets default values
AAdventureCharacter::AAdventureCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAdventureCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* playerController = Cast<APlayerController>(Controller)) //create a generic pointer to whatever is controlling this pawn (in this case a player)
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer())) // UEnhancedInputLocalPlayerSubsystem is the piece of code in charge of handling input context for Enhanced Input. // playerController->GetLocalPlayer() gets the local player object tied to this controller. // ULocalPlayer::GetSubsystem fetches the Enhanced Input Subsystem for that player
		{
			subsystem->AddMappingContext(PlayerMappingContext, 0); 
			UCharacterMovementComponent* charMov = playerController->GetCharacter()->GetCharacterMovement();
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("Class name: %s"), *GetClass()->GetName());
	UCharacterMovementComponent* CharMov = GetCharacterMovement();
	if (CharMov)
	{
		CharMov->SetMovementMode(MOVE_Walking);
	}

	if (Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character is possessed"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Character is NOT possessed"));
	}
}

void AAdventureCharacter::Move(const FInputActionValue& value)
{
	if (Controller != nullptr)
	{
		//Get a 2D vector (y = forward/backward, x = left/right)
		FVector2D movementVector = value.Get<FVector2D>();

		//Get forward and right direction
		const FRotator cameraRotation = Controller->GetControlRotation();
		const FRotator yawRotation(0.f, cameraRotation.Yaw, 0.f);

		const FVector forwardDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X); //Convert the yaw rotation into a matrix and extract the axis corresponding to X
		const FVector rightDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

		//Add Movement
		AddMovementInput(GetActorForwardVector(), movementVector.Y);
		AddMovementInput(FVector::RightVector, movementVector.X);
		/*UE_LOG(LogTemp, Warning, TEXT("Move X: %f"), movementVector.X);
		UE_LOG(LogTemp, Warning, TEXT("Move Y: %f"), movementVector.Y);*/

		//UCharacterMovementComponent* CharMov = GetCharacterMovement();
		//UE_LOG(LogTemp, Warning, TEXT("MovementMode: %d"), CharMov->MovementMode);

		UE_LOG(LogTemp, Warning, TEXT("Move X: %f, Y: %f"), movementVector.X, movementVector.Y);
	}
}

// Called every frame
void AAdventureCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//AddMovementInput(GetActorForwardVector(), 100.0f);

	/*FVector NewLocation = GetActorLocation();
	NewLocation.X += 200.f * DeltaTime;
	SetActorLocation(NewLocation);

	UCharacterMovementComponent* CharMov = GetCharacterMovement();
	if (!CharMov)
	{
		UE_LOG(LogTemp, Warning, TEXT("CharacterMovementComponent is NULL"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MaxWalkSpeed: %f, MovementMode: %d"),
			CharMov->MaxWalkSpeed, CharMov->MovementMode);
	}*/

}

// Called to bind functionality to input
void AAdventureCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) //By default unreal passes a generic UInputComponent, but since we are using the Enhanced Input Component we need to ensure the cast is valid (if it's not, CastChecked will cause an error)
	{
		enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAdventureCharacter::Move);
	}
}

