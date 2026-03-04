// Fill out your copyright notice in the Description page of Project Settings.


#include "AdventureCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAdventureCharacter::AAdventureCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);


	// Enable rotation toward movement direction
	bUseControllerRotationYaw = false; // Character rotation is independent
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character faces movement direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);

	// Controller input does not rotate spring arm
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	

	// Avoid camera rotation
	Camera->bUsePawnControlRotation = false; //?
	SpringArm->SetUsingAbsoluteRotation(true); //? // Keep spring arm rotation fixed

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

	UCharacterMovementComponent* CharMov = GetCharacterMovement();

	Interaction = FindComponentByClass<UInteractionComponent>();
}

void AAdventureCharacter::Move(const FInputActionValue& value)
{
	if (Controller != nullptr)
	{
		//Get a 2D vector (y = forward/backward, x = left/right)
		FVector2D movementVector = value.Get<FVector2D>();

		//Get forward and right direction
		const FRotator cameraRotation = Camera->GetComponentRotation();
		const FRotator yawRotation(0.f, cameraRotation.Yaw, 0.f);

		const FVector forwardDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X); //Convert the yaw rotation into a matrix and extract the axis corresponding to X
		const FVector rightDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

		//Add Movement
		AddMovementInput(forwardDir, movementVector.Y);
		AddMovementInput(rightDir, movementVector.X);
		//AddControllerYawInput(1 * FMath::Sign(movementVector.X));
	}
}

void AAdventureCharacter::Interact()
{
	Interaction->OnInteraction();
}

// Called every frame
void AAdventureCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAdventureCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) //By default unreal passes a generic UInputComponent, but since we are using the Enhanced Input Component we need to ensure the cast is valid (if it's not, CastChecked will cause an error)
	{
		enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAdventureCharacter::Move);
		enhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AAdventureCharacter::Interact);
	}
}

