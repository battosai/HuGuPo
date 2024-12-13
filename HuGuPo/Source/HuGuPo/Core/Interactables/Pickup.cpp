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
APickup::APickup()
{
    PrimaryActorTick.bCanEverTick = true;
}

// -----------------------------------------------------------------------------
void APickup::BeginPlay()
{
    Super::BeginPlay();

    mesh = Cast<UStaticMeshComponent>(
        GetDefaultSubobjectByName(TEXT("SM_Object")));
    check(mesh != nullptr);

    SetActorTickEnabled(false);

    bOverrideLook = false;
    use = EUse::Throwable;
}

// -----------------------------------------------------------------------------
void APickup::Tick(float delta_s)
{
    Super::Tick(delta_s);

    // Stops Tick function if object is not held and is not moving
    if (bHeld == false &&
        mesh->IsSimulatingPhysics() == true &&
        GetVelocity().Size() == 0.0)
    {
        mesh->SetSimulatePhysics(false);
        SetActorTickEnabled(false);
    }
}

// -----------------------------------------------------------------------------
void APickup::InstantInteract()
{
    bHeld = true;

    AVictim* victim = Cast<AVictim>(UGameplayStatics::GetPlayerCharacter(
        GetWorld(),
        0));

    mesh->SetSimulatePhysics(false);
    SetActorEnableCollision(false);

    AttachToActor(
        victim,
        FAttachmentTransformRules::SnapToTargetNotIncludingScale);

    // TODO:
    // Local transform is specific to lamp,
    // need to generalize these
    SetActorRelativeLocation(
        FVector(
            40, 
            50, 
            15),
        false,
        nullptr,
        ETeleportType::None);

    SetActorRelativeRotation(
        FQuat::MakeFromEuler(FVector(
            0,
            -20,
            0)),
        false,
        nullptr,
        ETeleportType::None);
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
            Throw();
            break;

        case EUse::Consumable:
            break;

        case EUse::Key:
            break;
        
        default:
            UE_LOG(
                LogTemp,
                Warning,
                TEXT("Unknown Pickup Use Type"));
            break;
    }
}

// -----------------------------------------------------------------------------
void APickup::Throw()
{
    bHeld = false;
    DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

    // Enable Tick to disable physics during throw
    SetActorTickEnabled(true);

    AVictim* victim = Cast<AVictim>(UGameplayStatics::GetPlayerCharacter(
        GetWorld(),
        0));

    // Enable physics and add force
    SetActorEnableCollision(true);
    mesh->SetSimulatePhysics(true);

    FVector force = victim->GetActorForwardVector() * mesh->GetMass() * 1000.0;
    mesh->AddImpulse(force);
}