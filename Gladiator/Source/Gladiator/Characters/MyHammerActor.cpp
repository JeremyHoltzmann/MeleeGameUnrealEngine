// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "MyHammerActor.h"


AMyHammerActor::AMyHammerActor(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP), canAttach(true), OwningPawn(nullptr)
{
}

bool AMyHammerActor::AttachWeaponToPawn(APawn* WeaponOwner, FString SkeletalCompName)
{
	if (!canAttach)
		return false;
	OwningPawn = WeaponOwner; // Sets the owner of this weapon. (Note: OwningPawn  is a APawn* member in my weapon class.)
	SetOwner(OwningPawn); // AActor::SetOwner(APawn*);
	DisableCollission();
	// A method i created to get any skeletal component from the owning pawn. (Could be made a template to function to get any type.)
	USkeletalMeshComponent* ArmMesh = GetPawnSkeletalComp(SkeletalCompName);

	if (ArmMesh) // Check to see if our rig Skeletal Mesh Component is good.
	{
		
		// AActor::AttachRootComponentTo(..)
		AttachRootComponentTo(ArmMesh, FName(TEXT("WeaponPoint")), EAttachLocation::SnapToTarget); // Attach the root component of our Weapon actor to the ArmMesh at the location of the socket.
		canAttach = true;
		return true; // Note: We can only assume it is attached, since epic did not provide a return value.
	}
	else
	{
		return false;
	}
}

void AMyHammerActor::ReceiveActorBeginOverlap(AActor* Other)
{
	if (Other != OwningPawn && OwningPawn != nullptr  && Other->GetClass() != OwningPawn->GetClass())
	{
		if (Other->IsA<AMyGladiatorCharacter>() && ((AMyGladiatorCharacter*)OwningPawn)->Attacking)
			((AMyGladiatorCharacter*)Other)->TakeHit();
	}
}

void AMyHammerActor::DisableCollission()
{
	DisableComponentsSimulatePhysics();
	SetActorEnableCollision(false);

	TArray<USkeletalMeshComponent*> Components;
	this->GetComponents<USkeletalMeshComponent>(Components);
	for (int32 i = 0; i < Components.Num(); i++)
	{
		Components[i]->bGenerateOverlapEvents = true;
		USkeletalMeshComponent* StaticMeshComponent = Components[i];
		StaticMeshComponent->BodyInstance.SetResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void AMyHammerActor::DropWeapon()
{
	SetActorEnableCollision(true);
	DetachRootComponentFromParent(true);
	TArray<USkeletalMeshComponent*> Components;
	this->GetComponents<USkeletalMeshComponent>(Components);
	TArray<UPrimitiveComponent*> ComponentsPrim;
	GetComponents(ComponentsPrim);
	for (UPrimitiveComponent* ComponentPrim : ComponentsPrim)
	{
		ComponentPrim->SetSimulatePhysics(true);
	}
	for (int32 i = 0; i < Components.Num(); i++)
	{
		USkeletalMeshComponent* StaticMeshComponent = Components[i];
		StaticMeshComponent->BodyInstance.SetResponseToAllChannels(ECollisionResponse::ECR_MAX);
		StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	canAttach = false;
	GetWorldTimerManager().SetTimer(this, &AMyHammerActor::CheckAttach, 5.0f, false);
	OwningPawn = nullptr;
}

void AMyHammerActor::CheckAttach()
{
	canAttach = true;
}

USkeletalMeshComponent* AMyHammerActor::GetPawnSkeletalComp(FString ComponentName)
{
	TArray<UActorComponent*> Components; // Array for Pawns components
	USkeletalMeshComponent* ArmMesh = NULL; // Will hold the skeletal mesh we want

	if (OwningPawn)
		OwningPawn->GetComponents(Components); // Get the components from the owning pawn

	for (UActorComponent* Comp : Components)
	{
		ArmMesh = Cast<USkeletalMeshComponent>(Comp); // Cast any component to Skeletal Comp.
		if (ArmMesh) // If we have a skeletal mesh
		{
			//if (ArmMesh->GetName() == "CharacterMesh0") // Check to see if its the one we want.
				return ArmMesh;
		}
	}

	return NULL; // Finished with out finding the component we wanted.
}