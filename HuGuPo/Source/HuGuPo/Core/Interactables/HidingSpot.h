/**
 * @brief Place that the player can hide in.
 */

#pragma once

// Standard library includes

// Unreal includes
#include "Components/SceneComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// HGP includes
#include <Core/Interactables/Interactable.h>

// Generated include
#include "HidingSpot.generated.h"

UCLASS(Abstract)
class HUGUPO_API AHidingSpot : public AActor, public IInteractable
{
    GENERATED_BODY()

    // Aliases

    public:

        /**
         * @brief
         */
        virtual void InstantInteract() override;

        /**
         * @brief
         */
        virtual void ProlongedInteract() override;

        /**
         * @brief
         */
        virtual void EndInteraction() override;

    protected:

    private:

        /**
         * Whether or not this spot is disabled.
         */
        UPROPERTY(EditDefaultsOnly)
        bool bDisabled;

        /**
         * @brief Whether or not this spot is occupied.
         */
        bool bOccupied;

        /**
         * @brief Timestamp of when an interaction started.
         */
        float interactionStart_s;

        /**
         * @brief Component with the transform of where the player hides.
         */
        USceneComponent* hideSpot;

        /**
         * @brief Component with the transform of where the player exits to.
         */
        USceneComponent* exitSpot;

        /**
         * Called when play begins for this component.
         */
        virtual void BeginPlay() override;
};