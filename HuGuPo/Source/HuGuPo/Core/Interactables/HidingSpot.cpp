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

    hideSpot = Cast<USceneComponent>(GetDefaultSubobjectByName(TEXT("HideSpot")));
    exitSpot = Cast<USceneComponent>(GetDefaultSubobjectByName(TEXT("ExitSpot")));
    check(hideSpot != nullptr);
    check(exitSpot != nullptr);
}

// -----------------------------------------------------------------------------
void AHidingSpot::InstantInteract() 
{
    if (bOccupied == false)
    {
        return;
    }

    // Leave hiding spot
    AVictim* victim = Cast<AVictim>(UGameplayStatics::GetPlayerCharacter(
        GetWorld(),
        0));

    victim->SetActorLocation(
        exitSpot->GetComponentLocation(), // will probably need to add offset for char height
        false,
        nullptr,
        ETeleportType::None);

    bOccupied = false;
}

// -----------------------------------------------------------------------------
void AHidingSpot::ProlongedInteract()
{
    if (bDisabled == true ||
        bOccupied == true)
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

    // Enter hiding spot
    if (time_s - interactionStart_s >= hideTime_s)
    {
        AVictim* victim = Cast<AVictim>(UGameplayStatics::GetPlayerCharacter(
            GetWorld(),
            0));

        victim->SetActorLocation(
            hideSpot->GetComponentLocation(),
            false,
            nullptr,
            ETeleportType::None);

        victim->SetActorRotation(
            hideSpot->GetComponentRotation(),
            ETeleportType::None);

        bOccupied = true;
    }
}

// -----------------------------------------------------------------------------
void AHidingSpot::EndInteraction() 
{
    interactionStart_s = -1.0;
}