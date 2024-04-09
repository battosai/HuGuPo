/**
 * @brief Main player character.
 */

// Module-specific include
#include "Victim.h"

// Standard library includes

// Unreal includes
#include "GameFramework/Actor.h"

// HGP includes
#include <Core/Interactables/Interactable.h>

// -----------------------------------------------------------------------------
void AVictim::BeginPlay()
{
	Super::BeginPlay();

	cam = FindComponentByClass<UCameraComponent>();

	check(cam != nullptr);
}

// -----------------------------------------------------------------------------
void AVictim::SetupPlayerInputComponent(UInputComponent* inputComponent)
{
	// Verify BP references are set
	check(defaultIMC != nullptr);
	check(walkIA != nullptr);
	check(lookIA != nullptr);
	check(instantInteractIA != nullptr);
	check(prolongedInteractIA != nullptr);

	Super::SetupPlayerInputComponent(inputComponent);

	// Add input mapping context
	controller = Cast<APlayerController>(GetController());

	ULocalPlayer* localPlayer = 
		Cast<ULocalPlayer>(controller->GetLocalPlayer());

	UEnhancedInputLocalPlayerSubsystem* eInputSystem = 
		localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	eInputSystem->AddMappingContext(
		defaultIMC, 
		0);

	// Bind InputActions to delegates
    UEnhancedInputComponent* eInput = 
		Cast<UEnhancedInputComponent>(inputComponent);

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

	eInput->BindAction(
		instantInteractIA, 
		ETriggerEvent::Triggered, 
		this, 
		&AVictim::InstantInteract);

	eInput->BindAction(
		prolongedInteractIA,
		ETriggerEvent::Triggered,
		this,
		&AVictim::ProlongedInteract);
}

// -----------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------
void AVictim::Look(const FInputActionValue& input)
{
	FVector2D value = input.Get<FVector2D>();

	AddControllerYawInput(value.X);
	AddControllerPitchInput(-value.Y);
}

// -----------------------------------------------------------------------------
void AVictim::InstantInteract(const FInputActionValue& input)
{
	FHitResult hitInfo;

	FVector start = cam->GetComponentLocation();
	FVector end = start + cam->GetForwardVector() * 300.0;

	bool hit = GetWorld()->LineTraceSingleByChannel(
		hitInfo,
		start,
		end,
		InteractTraceChannel);

	if (hit == false)
	{
		return;
	}

	// Get ActorComponents that implement IInteractable
	AActor* actor = hitInfo.HitObjectHandle.FetchActor();
	auto components = actor->GetComponentsByInterface(UInteractable::StaticClass());

	if (components.Num() == 0)
	{
		UE_LOG(
			LogTemp,
			Log,
			TEXT("%s IS NOT INTERACTABLE"),
			*(actor->GetActorLabel()));

		return;
	}

	UE_LOG(
		LogTemp,
		Log,
		TEXT("INTERACTING WITH %s"),
		*(actor->GetActorLabel()));

	// Do the interactions
	for (int ii = 0;
		ii < components.Num();
		ii++)
	{
		IInteractable* interactable = Cast<IInteractable>(components[ii]);
		interactable->InstantInteract();
	}
}

// -----------------------------------------------------------------------------
void AVictim::ProlongedInteract(const FInputActionValue& input)
{
	return;
}