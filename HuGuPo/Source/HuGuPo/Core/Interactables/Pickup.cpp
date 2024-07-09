/**
 * @brief Object that can be picked up.
 */

// Module-specific include
#include "Pickup.h"

// Standard library includes

// Unreal includes
#include "Kismet/GameplayStatics.h"

// HGP includes
#include <Core/Characters/Victim.h>

// -----------------------------------------------------------------------------
void APickup::BeginPlay()
{
    Super::BeginPlay();

    mesh = Cast<UStaticMeshComponent>(
        GetDefaultSubobjectByName(TEXT("StaticMesh")));

    bOverrideLook = false;
    use = EUse::Throwable;
}

// -----------------------------------------------------------------------------
void APickup::InstantInteract()
{
    bHeld = !bHeld;

    AVictim* victim = Cast<AVictim>(UGameplayStatics::GetPlayerCharacter(
        GetWorld(),
        0));

    SetActorEnableCollision(false);

    AttachToActor(
        victim,
        FAttachmentTransformRules::SnapToTargetIncludingScale);

    AddActorLocalOffset(
        FVector(
            50, 
            50, 
            0),
        false,
        nullptr,
        ETeleportType::None);

    // FQuat::MakeFromEuler(FVector(0, -20, 0))
}

// -----------------------------------------------------------------------------
void APickup::ProlongedInteract() {}

// -----------------------------------------------------------------------------
void APickup::EndInteraction() {}

// -----------------------------------------------------------------------------
void APickup::Use()
{
    switch (use)
    {
        case EUse::Throwable:
            break;
        
        default:
            UE_LOG(
                LogTemp,
                Warning,
                TEXT("Unknown APickup::EUse"));
            break;
    }
}