// Standard library includes

// Uncreal includes

// HGP includes

// Module-specific include
#include "Victim.h"

void AVictim::SetupPlayerInputComponent(UInputComponent* inputComponent)
{
	// Verify BP references are set
	check(defaultIMC != nullptr);
	check(walkIA != nullptr);
	check(lookIA != nullptr);

	Super::SetupPlayerInputComponent(inputComponent);

	// Add input mapping context
	APlayerController* controller = Cast<APlayerController>(GetController());
	ULocalPlayer* localPlayer = Cast<ULocalPlayer>(controller->GetLocalPlayer());
	UEnhancedInputLocalPlayerSubsystem* eInputSystem = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	eInputSystem->AddMappingContext(
		defaultIMC, 
		0);

	// Bind InputActions to delegates
    UEnhancedInputComponent* eInput = Cast<UEnhancedInputComponent>(inputComponent);

	eInput->BindAction(
		walkIA, 
		ETriggerEvent::Triggered, 
		this, 
		&AVictim::Walk);

	eInput->BindAction(
		lookIA, 
		ETriggerEvent::Triggered, 
		this, 
		&AVictim::Look);
}

void AVictim::Walk(const FInputActionValue& input)
{
	FVector2D value = input.Get<FVector2D>();

	FVector forward = GetActorForwardVector() * value.X;
	FVector right = GetActorRightVector() * value.Y;
	FVector movement = forward + right;

	AddMovementInput(
		movement,
		1.0,
		false);
}

void AVictim::Look(const FInputActionValue& input)
{
	FVector2D value = input.Get<FVector2D>();

	AddControllerYawInput(value.X);
	AddControllerPitchInput(-value.Y);
}