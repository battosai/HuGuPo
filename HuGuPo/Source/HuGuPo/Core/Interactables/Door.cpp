/**
 * @brief Interactable door.
 */

// Module-specific include
#include "Door.h"

// Standard library includes

// Unreal includes
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"

// HGP includes

// -----------------------------------------------------------------------------
void ADoor::BeginPlay()
{
    Super::BeginPlay();

    state = static_cast<State>(startState);

    doorMesh = Cast<UStaticMeshComponent>(
        GetDefaultSubobjectByName(TEXT("DoorStaticMesh")));

    victim = Cast<AVictim>(UGameplayStatics::GetPlayerCharacter(
        GetWorld(),
        0));
}

// -----------------------------------------------------------------------------
void ADoor::InstantInteract()
{
    // switch (state)
    // {
    //     case State::LOCKED:
    //         return;

    //     case State::CLOSED:
    //         state = State::OPENED;
    //         doorMesh->SetRelativeRotation(openRotation);
    //         break;

    //     case State::OPENED:
    //         state = State::CLOSED;
    //         doorMesh->SetRelativeRotation(closedRotation);
    //         break;
    // }
}

// -----------------------------------------------------------------------------
void ADoor::ProlongedInteract()
{
    const FVector2D mouseMovement = victim->GetMouseMovement();

    float dot = FVector::DotProduct(
        victim->GetActorForwardVector(),
        doorMesh->GetForwardVector());

    const float degreesPerInput = 10.0;

    // Push side
    if (dot >= 0.0)
    {
        doorMesh->AddLocalRotation(
            FQuat::MakeFromEuler(
                FVector(
                    -mouseMovement.X * degreesPerInput,
                    0,
                    0)));
    }

    UE_LOG(
        LogTemp,
        Log,
        TEXT("PEEKIN DOOR WITH MOUSE MVMNT: (%f, %f), PLAYER DOT: %f"),
        mouseMovement.X,
        mouseMovement.Y,
        dot);
}