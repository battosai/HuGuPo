/**
 * @brief Interface for interactable objects.
 */

#pragma once

// Standard library includes

// Unreal includes
#include "CoreMinimal.h"
#include "UObject/Interface.h"

// HGP includes

// Generated include
#include "Interactable.generated.h"

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
    GENERATED_BODY()
};

class IInteractable
{
    GENERATED_BODY()

    // Aliases

    public:

        /**
         * @brief What happens when the player interacts with this object.
         * Interaction that starts and ends immediately. Single interaction.
         * Set as pure virtual so that it has to be inherited to be implemented.
         */
        virtual void InstantInteract() = 0;

        /**
         * @brief What happens when the player interacts with this object.
         * Interaction that starts and continues for as long as the player is
         * still interacting. 
         * Set as pure virtual so that it has to be inherited to be implemented.
         */
        virtual void ProlongedInteract() = 0;

    protected:

    private:

};