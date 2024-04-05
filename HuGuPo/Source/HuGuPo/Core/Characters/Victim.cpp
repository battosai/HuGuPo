// Standard library includes

// Uncreal includes

// HGP includes

// Module-specific include
#include "Victim.h"

void AVictim::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	// Verify BP references are set
	check(IMC_Default != nullptr);
	check(IA_Walk != nullptr);

	Super::SetupPlayerInputComponent(playerInputComponent);

	// Add input mapping context
	APlayerController* controller = Cast<APlayerController>(GetController());
	ULocalPlayer* localPlayer = Cast<ULocalPlayer>(controller->GetLocalPlayer());
	UEnhancedInputLocalPlayerSubsystem* eInputSystem = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	eInputSystem->AddMappingContext(
		IMC_Default, 
		0);

	// Bind InputActions to delegates
    UEnhancedInputComponent* eInput = Cast<UEnhancedInputComponent>(playerInputComponent);

	eInput->BindAction(
		IA_Walk, 
		ETriggerEvent::Started, 
		this, 
		&AVictim::Walk);

}

void AVictim::Walk(const FInputActionValue& input)
{
	FVector2D value = input.Get<FVector2D>();

	UE_LOG(
		LogTemp,
		Log,
		TEXT("INPUT FOR WALK: (%f, %f)"),
		value.X,
		value.Y);

	return;
}
