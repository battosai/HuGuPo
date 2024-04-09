/**
 * @brief Interactable door.
 */

// Module-specific include
#include "Door.h"

// Standard library includes

// Unreal includes

// HGP includes

// -----------------------------------------------------------------------------
void UDoor::BeginPlay()
{
    Super::BeginPlay();

    state = static_cast<State>(startState);
}

// -----------------------------------------------------------------------------
void UDoor::InstantInteract()
{
    switch (state)
    {
        case State::LOCKED:
            return;

        case State::CLOSED:
            state = State::OPENED;
            GetOwner()->SetActorRelativeRotation(openRotation);
            break;

        case State::OPENED:
            state = State::CLOSED;
            GetOwner()->SetActorRelativeRotation(closedRotation);
            break;
    }
}