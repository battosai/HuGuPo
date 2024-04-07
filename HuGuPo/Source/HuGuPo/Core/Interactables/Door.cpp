/**
 * @brief Interactable door.
 */

// Standard library includes

// Unreal includes

// HGP includes

// Module-specific include
#include "Door.h"

// -----------------------------------------------------------------------------
void UDoor::Interact()
{
    switch (state)
    {
        case State::LOCKED:
            UE_LOG(
                LogTemp,
                Log,
                TEXT("INTERACTABLE DOOR: I'm locked!"));

            return;
            break;

        case State::CLOSED:
            state = State::OPENED;
            break;

        case State::OPENED:
            state = State::CLOSED;
            break;
    }

    UE_LOG(
        LogTemp,
        Log,
        TEXT("INTERACTING WITH DOOR INTERACTABLE"));
}