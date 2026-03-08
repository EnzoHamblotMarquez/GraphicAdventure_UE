#include "AdventureCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"

#include "GameFramework/CharacterMovementComponent.h"

AAdventureCharacter::AAdventureCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);

	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera->bUsePawnControlRotation = false;
	SpringArm->SetUsingAbsoluteRotation(true);

}

void AAdventureCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* playerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
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
		FVector2D movementVector = value.Get<FVector2D>();

		const FRotator cameraRotation = Camera->GetComponentRotation();
		const FRotator yawRotation(0.f, cameraRotation.Yaw, 0.f);

		const FVector forwardDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		const FVector rightDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(forwardDir, movementVector.Y);
		AddMovementInput(rightDir, movementVector.X);
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


	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAdventureCharacter::Move);
		enhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AAdventureCharacter::Interact);
	}
}

