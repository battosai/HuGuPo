/**
 * @brief Interactable door.
 */

#pragma once

// Standard library includes

// Unreal includes
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// HGP includes
#include <Core/Characters/Victim.h>
#include <Core/Interactables/Interactable.h>

// Generated include
#include "Door.generated.h"

UCLASS(Abstract)
class HUGUPO_API ADoor : public AActor, public IInteractable
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
        UPROPERTY(EditDefaultsOnly, meta=(ClampMin = "0", ClampMax = "2"))
        int startState;

        /**
         * @brief What happens when the player interacts with this object.
         */
        virtual void InstantInteract() override;

        /**
         * @brief Interaction that occurs while player is still interacting with
         * this object.
         */
        virtual void ProlongedInteract() override;

    protected:

    private:

        /**
         * @brief Quaternion for closed state.
         */
        const FQuat closedRotation = FQuat::MakeFromEuler(FVector(0, 0, 0));

        /**
         * @brief Quaternion for open state.
         */
        const FQuat openRotation = FQuat::MakeFromEuler(FVector(0, 0, -90));

        /**
         * @brief Current state of this door.
         */
        State state;

        /**
         * @brief Reference to the static mesh of the door.
         */
        UStaticMeshComponent* doorMesh;

        /**
         * @brief Reference to victim character.
         */
        AVictim* victim;

        /**
		 * @brief Called when play begins for this component.
         */
        virtual void BeginPlay() override;
};