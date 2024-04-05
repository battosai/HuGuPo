#pragma once

// Standard library includes

// Unreal includes
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

/**
 * @brief Main player character.
 */
UCLASS(Abstract)
class HUGUPO_API AVictim : public ACharacter
{
	GENERATED_BODY()

	// Aliases

	public:

	protected:

	private:

		/**
		 * @brief Default InputMappingContext reference.
		 */
		UPROPERTY(EditDefaultsOnly)
		UInputMappingContext* defaultIMC;
	
		/**
		 * @brief Walk InputAction reference.
		 */
		UPROPERTY(EditDefaultsOnly)
		UInputAction* walkIA;

		/**
		 * @brief Look InputAction reference.
		 */
		UPROPERTY(EditDefaultsOnly)
		UInputAction* lookIA;

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
};
