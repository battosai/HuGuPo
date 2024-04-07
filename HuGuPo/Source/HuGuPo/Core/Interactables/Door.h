/**
 * @brief Interactable door.
 */

#pragma once

// Standard library includes

// Unreal includes
#include "Components/ActorComponent.h"
#include "CoreMinimal.h"

// HGP includes
#include <Core/Interactables/Interactable.h>

// Generated include
#include "Door.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class HUGUPO_API UDoor : public UActorComponent, public IInteractable
{
    GENERATED_BODY()

    // Aliases

    public:

        /**
         * @brief State of door.
         */
        enum State 
        {
            CLOSED,
            OPENED,
            LOCKED
        };

        /**
         * @brief Current state of this door.
         */
        State state;

        /**
         * @brief What happens when the player interacts with this object.
         */
        virtual void Interact() override;

    protected:

    private:

};