/**
 * @brief Object that can be picked up.
 */

#pragma once

// Standard library includes

// Unreal includes
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// HGP includes
#include <Core/Interactables/Interactable.h>

// Generated include
#include "Pickup.generated.h"

UCLASS()
class HUGUPO_API APickup : public AActor, public IInteractable
{
    GENERATED_BODY()

    // Aliases

    public:

        /**
         * @brief Usage of item once picked up.
         */
        enum EUse
        {
            Throwable = 0,
            Consumable = 1,
            Key = 2,
        };

        /**
         * @brief What happens when the player interacts with this object.
         * Implements a Pickup interaction if object is on the floor or Use 
         * interaction if object is held.
         */
        virtual void InstantInteract() override;

        /**
         * @brief Interaction that occurs while player is still interacting with this object. 
         * Do nothing.
         */
        virtual void ProlongedInteract() override;

        /**
         * @brief What happens when the player interaction ends.
         * Do nothing.
         */
        virtual void EndInteraction() override;

        /**
         * @brief What happens when the player uses this item.
         */
        void Use();

    protected:

    private:

        /**
         * @brief Whether or not this pickup is held by the player.
         */
        bool bHeld;

        /**
         * @brief Usage of this item once picked up.
         */
        EUse use;

        /**
         * @brief Reference to the static mesh of this pickup item.
         */
        UStaticMeshComponent* mesh;

        /**
         * @brief Called when play begins for this component.
         */
        virtual void BeginPlay() override;
};