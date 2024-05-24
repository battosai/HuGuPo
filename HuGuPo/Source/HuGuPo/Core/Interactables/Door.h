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
         * @brief Orientation of door to player.
         */
        enum EOrientation 
        {
            Undetermined = 0,
            PushToOpen = 1,
            PushToClose = 2
        };

        /**
         * @brief What happens when the player interacts with this object.
         * Do nothing.
         */
        virtual void InstantInteract() override;

        /**
         * @brief Interaction that occurs while player is still interacting with
         * this object. Implements a peeking door mechanic based on player mouse
         * movement.
         */
        virtual void ProlongedInteract() override;

        /**
         * @brief What happens when the player interaction ends.
         * Clears the orientation of the door to player.
         */
        virtual void EndInteraction() override;

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
         * @brief Reference to the static mesh of the door.
         */
        UStaticMeshComponent* doorMesh;

        /**
         * @brief Reference to victim character.
         */
        AVictim* victim;

        /**
         * @brief Orientation of door to player at start of interaction.
         */
        EOrientation orientation;

        /**
		 * @brief Called when play begins for this component.
         */
        virtual void BeginPlay() override;
};