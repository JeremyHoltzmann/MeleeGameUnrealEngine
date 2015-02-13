// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MyGladiatorCharacter.generated.h"


/**
 * 
 */


class AMyHammerActor;
class AMyShieldActor;

UCLASS()
class GLADIATOR_API AMyGladiatorCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()


	AMyHammerActor* Hammer;
	AMyShieldActor* Shield;

	bool Attacking;

	void Attack();

	void TurnRate(float Value);
	void LookRate(float Value);

	void MoveForward(float Value);
	void MoveRight(float Value);
	
	void BeginPlay() override;

	void ChangeAttack();

	void DropWeapon();

	void DisableCollission();
	virtual void IsDead();

	int32 GetHealth();
	int32 GetMaxHealth();

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

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;	
	public:
		void TakeHit();
		
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Director)
		int32 MaxPV;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Director)
		int32 PV;

		TSubclassOf<AMyHammerActor> HammerActor;
		TSubclassOf<AMyShieldActor> ShieldActor;
};
