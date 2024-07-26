/**
 * @brief Place that the player can hide in.
 */

// Module-specific include
#include "HidingSpot.h"

// Standard library includes

// Unreal includes
#include "Kismet/GameplayStatics.h"

// HGP includes
#include <Core/Characters/Victim.h>

// -----------------------------------------------------------------------------
void AHidingSpot::BeginPlay()
{
    Super::BeginPlay();

    spot = Cast<USceneComponent>(GetDefaultSubobjectByName(TEXT("Spot")));
    check(spot != nullptr);
}

// -----------------------------------------------------------------------------
void AHidingSpot::InstantInteract() 
{
    if (bOccupied == false)
    {
        return;
    }

    // Leave spot
    bOccupied = false;
}

// -----------------------------------------------------------------------------
void AHidingSpot::ProlongedInteract()
{
    if (bDisabled == true ||
        bOccupied == true ||
        spot == nullptr)
    {
        return;
    }

    // Hold interact for a bit to enter hiding spot
    float time_s = GetWorld()->GetTimeSeconds();

    if (interactionStart_s < 0)
    {
        interactionStart_s = GetWorld()->GetTimeSeconds();
    }

    const float hideTime_s = 1.0;

    // Enter spot
    if (time_s - interactionStart_s >= hideTime_s)
    {
        AVictim* victim = Cast<AVictim>(UGameplayStatics::GetPlayerCharacter(
            GetWorld(),
            0));

        victim->SetActorLocation(
            spot->GetComponentLocation(),
            false,
            nullptr,
            ETeleportType::None);

        victim->SetActorRotation(
            spot->GetComponentRotation(),
            ETeleportType::None);

        bOccupied = true;
    }
}

// -----------------------------------------------------------------------------
void AHidingSpot::EndInteraction() 
{
    interactionStart_s = -1.0;
}