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

UCLASS(meta=(BlueprintSpawnableComponent))
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
            CLOSED = 0,
            OPENED = 1,
            LOCKED = 2
        };

        /**
         * @brief Starting State of door.
         * Clamped to the integer range of State enum.
         */
        UPROPERTY(
            EditInstanceOnly, 
            meta=(
                ClampMin = "0", 
                ClampMax = "2"))
        int startState;

        /**
         * @brief What happens when the player interacts with this object.
         */
        virtual void Interact() override;

    protected:

    private:

        /**
         * @brief Quaternion for closed state.
         */
        FQuat closedRotation = FQuat::MakeFromEuler(FVector(0, 0, 180));

        /**
         * @brief Quaternion for open state.
         */
        FQuat openRotation = FQuat::MakeFromEuler(FVector(0, 0, 90));

        /**
         * @brief Current state of this door.
         */
        State state;

        /**
		 * @brief Called when play begins for this component.
         */
        virtual void BeginPlay() override;
};