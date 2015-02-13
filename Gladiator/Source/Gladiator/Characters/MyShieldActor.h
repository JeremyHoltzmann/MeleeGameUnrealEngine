// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MyShieldActor.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API AMyShieldActor : public AActor
{
	GENERATED_UCLASS_BODY()

	APawn* OwningPawn;
	bool canAttach;

	void DisableCollission();
	void CheckAttach();
	virtual void ReceiveHit
		(
	class UPrimitiveComponent * MyComp,
	class AActor * Other,
	class UPrimitiveComponent * OtherComp,
		bool bSelfMoved,
		FVector HitLocation,
		FVector HitNormal,
		FVector NormalImpulse,
		const FHitResult & Hit
		) override;

public:
	USkeletalMeshComponent* GetPawnSkeletalComp(FString ComponentName);
	bool AttachWeaponToPawn(APawn* WeaponOwner, FString SkeletalCompName);
	void DropWeapon();
	
};
