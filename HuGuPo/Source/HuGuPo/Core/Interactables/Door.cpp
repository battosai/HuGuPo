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

    doorMesh = Cast<UStaticMeshComponent>(
        GetDefaultSubobjectByName(TEXT("DoorStaticMesh")));

    victim = Cast<AVictim>(UGameplayStatics::GetPlayerCharacter(
        GetWorld(),
        0));

    bOverrideLook = true;
    orientation = EOrientation::Undetermined;
}

// -----------------------------------------------------------------------------
void ADoor::InstantInteract() {}

// -----------------------------------------------------------------------------
void ADoor::ProlongedInteract()
{
    // Cache starting orientation
    if (orientation == EOrientation::Undetermined)
    {
        int flipFactor = bFlippedDoor ?
            -1 :
            1;

        float dot = FVector::DotProduct(
            victim->GetActorForwardVector(),
            -flipFactor * (doorMesh->GetRightVector()));

        orientation = (dot >= 0.0) ?
            EOrientation::PushToOpen :
            EOrientation::PushToClose;
    }

    // Filter out small jitters
    const float threshold = 0.1;
    const FVector2D mouseMovement = victim->GetMouseMovement();

    if (abs(mouseMovement.X) < threshold)
    {
        return;
    }

    // Apply movement
    const float degreesPerInput = 1.0;
    int orientationFactor = (orientation == EOrientation::PushToOpen) ?
        1 :
        -1;

    doorMesh->AddLocalRotation(
        FQuat::MakeFromEuler(
            FVector(
                0,
                0,
                mouseMovement.X * degreesPerInput * orientationFactor)));
}

// -----------------------------------------------------------------------------
void ADoor::EndInteraction()
{
    orientation = EOrientation::Undetermined;
}