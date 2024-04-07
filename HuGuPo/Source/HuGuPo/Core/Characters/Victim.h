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
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputTriggers.h"

// HGP includes

// Generated include
#include "Victim.generated.h"

UCLASS(Abstract)
class HUGUPO_API AVictim : public ACharacter
{
	GENERATED_BODY()

	// Aliases
	#define InteractTraceChannel ECC_GameTraceChannel1

	public:

	protected:

	private:

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
		 * @brief Interact InputAction reference.
		 */
		UPROPERTY(EditDefaultsOnly, Category="Input")
		UInputAction* interactIA;

		/**
		 * @brief Reference to this character's PlayerController.
		 */
		APlayerController* controller;

		/**
		 * @brief Reference to this character's CameraComponent.
		 */
		UCameraComponent* cam;

		/**
		 * @brief Called when play begins for this actor.
		 */
		virtual void BeginPlay() override;

		/**
		 * @brief Setup input.
		 */
		virtual void SetupPlayerInputComponent(UInputComponent* playerInputComponent) override;

		/**
		 * @brief Walk InputAction delegate.
		 */
		void Walk(const FInputActionValue& input);

		/**
		 * @brief Look InputAction delegate.
		 */
		void Look(const FInputActionValue& input);

		/**
		 * @brief Interact InputAction delegate.
		 */
		void Interact(const FInputActionValue& input);
};
