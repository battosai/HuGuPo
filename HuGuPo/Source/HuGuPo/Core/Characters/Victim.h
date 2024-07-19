/**
 * @brief Main player character.
 */

#pragma once

// Standard library includes

// Unreal includes
#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputTriggers.h"

// HGP includes
#include <Core/Interactables/Interactable.h>
#include <Core/Interactables/Pickup.h>

// Generated include
#include "Victim.generated.h"

UCLASS(Abstract)
class HUGUPO_API AVictim : public ACharacter
{
	GENERATED_BODY()

	// Aliases
	#define InteractTraceChannel ECC_GameTraceChannel1

	public:

		/**
		 * @brief Get mouse movement input.
		 */
		const FVector2D& GetMouseMovement()
		{
			return mouseMovementInput;
		}

	protected:

	private:

		/**
		 * @brief Whether or not the player should ignore interactables.
		 */
		bool bIgnoreInteractables;

		/**
		 * @brief Reference to an interactable that the player is focused on.
		 */
		IInteractable* focusedInteractable;

		/**
		 * @brief Default InputMappingContext reference.
		 */
		UPROPERTY(EditDefaultsOnly, Category="Input")
		UInputMappingContext* defaultIMC;
	
		/**
		 * @brief Walk InputAction reference.
		 */
		UPROPERTY(EditDefaultsOnly, Category="Input")
		UInputAction* walkIA;

		/**
		 * @brief Look InputAction reference.
		 */
		UPROPERTY(EditDefaultsOnly, Category="Input")
		UInputAction* lookIA;

		/**
		 * @brief Jump InputAction reference.
		 */
		UPROPERTY(EditDefaultsOnly, Category="Input")
		UInputAction* jumpIA;

		/**
		 * @brief Instant Interact InputAction reference.
		 */
		UPROPERTY(EditDefaultsOnly, Category="Input")
		UInputAction* instantInteractIA;

		/**
		 * @brief Prolonged Interact InputAction reference.
		 */
		UPROPERTY(EditDefaultsOnly, Category="Input")
		UInputAction* prolongedInteractIA;

		/**
		 * @brief Use InputAction reference.
		 */
		UPROPERTY(EditDefaultsOnly, Category="Input")
		UInputAction* useIA;

		/**
		 * @brief Reference to this character's PlayerController.
		 */
		APlayerController* controller;

		/**
		 * @brief Reference to this character's CameraComponent.
		 */
		UCameraComponent* cam;

		/**
		 * @brief Reference to this character's mesh component.
		 */
		UMeshComponent* mesh;

		/**
		 * @brief Current input for mouse movement.
		 * Only updated when Look InputAction is not consuming it.
		 */
		FVector2D mouseMovementInput;

		/**
		 * @brief Item held in hand.
		 */
		APickup* item;

		// -------------------------------------------------------------------------
		// Unreal Behaviour
		// -------------------------------------------------------------------------

		/**
		 * @brief Called when play begins for this actor.
		 */
		virtual void BeginPlay() override;

		/**
		 * @brief Setup input.
		 */
		virtual void SetupPlayerInputComponent(UInputComponent* playerInputComponent) override;

		/**
		 * @brief Update loop.
		 */
		virtual void Tick(float deltaSeconds) override;

		/**
		 * @brief Walk InputAction delegate.
		 */
		void Walk(const FInputActionValue& input);

		/**
		 * @brief Look InputAction delegate.
		 */
		void Look(const FInputActionValue& input);

		/**
		 * @brief Jump InputAction delegate.
		 */
		void AttemptJump(const FInputActionValue& input);

		/**
		 * @brief Instant Interact InputAction delegate.
		 */
		void InstantInteract(const FInputActionValue& input);

		/**
		 * @brief Prolonged Interact InputAction delegate.
		 */
		void ProlongedInteract(const FInputActionValue& input);

		/**
		 * @brief Interact InputActions ending delegate.
		 */
		void EndInteraction(const FInputActionValue& input);

		/**
		 * @brief Use InputAction delegate.
		 */
		void Use(const FInputActionValue& input);

		/**
		 * @brief Line trace to find an Interactable component on an object.
		 */
		IInteractable* GetInteractable();
};
