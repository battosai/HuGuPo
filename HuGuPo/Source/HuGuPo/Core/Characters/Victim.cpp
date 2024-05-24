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

	bIgnoreInteractables = false;
	focusedInteractable = nullptr;
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

	eInput->BindAction(
		prolongedInteractIA,
		ETriggerEvent::Completed,
		this,
		&AVictim::EndInteraction);
}

// -----------------------------------------------------------------------------
void AVictim::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	if (focusedInteractable != nullptr)
	{
		focusedInteractable->ProlongedInteract();
	}
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

	// If we are interacting with something, store the input
	// otherwise set the input storage to (0, 0)
	if (focusedInteractable != nullptr)
	{
		mouseMovementInput = value;
		return;
	}
	else
	{
		mouseMovementInput = FVector2D::ZeroVector;
	}

	AddControllerYawInput(value.X);
	AddControllerPitchInput(-value.Y);
}

// -----------------------------------------------------------------------------
void AVictim::InstantInteract(const FInputActionValue& input)
{
	if (bIgnoreInteractables == true)
	{
		return;
	}

	IInteractable* interactable = GetInteractable();

	if (interactable == nullptr)
	{
		return;
	}

	interactable->InstantInteract();
}

// -----------------------------------------------------------------------------
void AVictim::ProlongedInteract(const FInputActionValue& input)
{
	if (bIgnoreInteractables == true)
	{
		return;
	}

	focusedInteractable = GetInteractable();

	if (focusedInteractable == nullptr)
	{
		UE_LOG(
			LogTemp,
			Log,
			TEXT("No interactable"));

		bIgnoreInteractables = true;
		return;
	}

	focusedInteractable->ProlongedInteract();
}

// -----------------------------------------------------------------------------
void AVictim::EndInteraction(const FInputActionValue& input)
{
	bIgnoreInteractables = false;
	focusedInteractable = nullptr;
}

// -----------------------------------------------------------------------------
IInteractable* AVictim::GetInteractable()
{
	FHitResult hitInfo;

	FVector start = cam->GetComponentLocation();
	FVector end = start + cam->GetForwardVector() * 300.0;

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		hitInfo,
		start,
		end,
		InteractTraceChannel);

	if (bHit == false)
	{
		return nullptr;
	}

	// Return IInteractable casted actor
	AActor* actor = hitInfo.HitObjectHandle.FetchActor();
	IInteractable* interactable = Cast<IInteractable>(actor);
	return interactable;
}