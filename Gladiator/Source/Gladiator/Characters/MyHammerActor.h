// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MyGladiatorCharacter.h"
#include "MyHammerActor.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API AMyHammerActor : public AActor
{
	GENERATED_UCLASS_BODY()
		APawn* OwningPawn;
		bool canAttach;

		void DisableCollission();
		void CheckAttach();


	private:
		void ReceiveActorBeginOverlap(AActor* Other);

	public :
		USkeletalMeshComponent* GetPawnSkeletalComp(FString ComponentName);
		bool AttachWeaponToPawn(APawn* WeaponOwner, FString SkeletalCompName);
		void DropWeapon();
};
