// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "MyHammerActor.h"
#include "MyShieldActor.h"
#include "MyGladiatorCharacter.h"
#include "../MyCharacterAnimInstance.h"

AMyGladiatorCharacter::AMyGladiatorCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP), Attacking(false), Shield(nullptr), Hammer(nullptr), MaxPV(5)
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Blueprints/MyHammerBP.MyHammerBP'"));
	if (ItemBlueprint.Object)
		HammerActor = (UClass*)ItemBlueprint.Object->GeneratedClass;
	//
	static ConstructorHelpers::FObjectFinder<UBlueprint> ShieldBP(TEXT("Blueprint'/Game/Blueprints/MyShieldBP.MyShieldBP'"));
	if (ShieldBP.Object)
		ShieldActor = (UClass*)ShieldBP.Object->GeneratedClass;

	PV = MaxPV;
}


void AMyGladiatorCharacter::TurnRate(float value)
{
	float TurnRotationRate = 40.0f;
	AddControllerYawInput(TurnRotationRate * value * GetWorld()->GetDeltaSeconds());
}

void AMyGladiatorCharacter::LookRate(float Value)
{
	float LookRotationRate = 40.0f;
	AddControllerPitchInput(LookRotationRate * Value * GetWorld()->GetDeltaSeconds());
}

int32 AMyGladiatorCharacter::GetHealth()
{
	return PV;
}

int32 AMyGladiatorCharacter::GetMaxHealth()
{
	return MaxPV;
}

void AMyGladiatorCharacter::MoveForward(float Value)
{
	if (Attacking) return;
	AController* PlayerController = GetController();
	if (PlayerController != nullptr)
	{
		FVector MoveDir = PlayerController->GetActorForwardVector();
		MoveDir.Z = 0.0f;
		if (!MoveDir.IsZero())
		{
			MoveDir.Normalize();
		}
		AddMovementInput(MoveDir, Value);
	}
}

void AMyGladiatorCharacter::MoveRight(float Value)
{
	if (Attacking) return;
	AController* PlayerController = GetController();
	if (PlayerController != nullptr)
	{
		FVector MoveDir = PlayerController->GetActorRightVector();
		AddMovementInput(MoveDir, Value);
	}
}

void AMyGladiatorCharacter::BeginPlay()
{
	Super::BeginPlay();
	UWorld* world = GetWorld();
	AMyHammerActor* hammer = nullptr;
	AMyShieldActor* shield = nullptr;

	if (world)
	{
		hammer = world->SpawnActor<AMyHammerActor>(HammerActor, FVector(0, 0, 0), FRotator(0, 0, 0));
		if (!Hammer)
		{
			((AMyHammerActor*)hammer)->AttachWeaponToPawn(this, "b_RightWeapon");
			Hammer = hammer;
		}
		shield = world->SpawnActor<AMyShieldActor>(ShieldActor, FVector(0, 0, 0), FRotator(0, 0, 0));
		if (!Shield)
		{
			((AMyShieldActor*)shield)->AttachWeaponToPawn(this, "b_LeftWeapon");
			Shield = shield;
		}

	}
}

void AMyGladiatorCharacter::ReceiveHit(
class UPrimitiveComponent * MyComp,
class AActor * Other,
class UPrimitiveComponent * OtherComp,
	bool bSelfMoved,
	FVector HitLocation,
	FVector HitNormal,
	FVector NormalImpulse,
	const FHitResult & Hit
	)
{
	if (Other->IsA<AMyHammerActor>() && Hammer == nullptr)
	{
		((AMyHammerActor*)Other)->AttachWeaponToPawn(this, "b_RightWeapon");
		Hammer = Cast<AMyHammerActor>(Other);
	}
	else if (Other->IsA<AMyShieldActor>() && Shield == nullptr)
	{
		((AMyShieldActor*)Other)->AttachWeaponToPawn(this, "b_LeftWeapon");
		Shield = Cast<AMyShieldActor>(Other);
	}
	else
	{
	}
}

void AMyGladiatorCharacter::TakeHit()
{
	--PV;
	if (PV == 0)
	{
		DropWeapon();
		if (Mesh != nullptr)
		{
			UMyCharacterAnimInstance* Animation = Cast<UMyCharacterAnimInstance>(Mesh->GetAnimInstance());
			if (!Animation) return;
				Animation->Dead = true;
			
			IsDead();
			DisableCollission();
		}
	}
}

void AMyGladiatorCharacter::IsDead()
{
}

void AMyGladiatorCharacter::DropWeapon()
{
	if (Attacking) return;
	if (Hammer != nullptr)
		((AMyHammerActor*)Hammer)->DropWeapon();
	if (Shield != nullptr)
		((AMyShieldActor*)Shield)->DropWeapon();
	Hammer = nullptr;
	Shield = nullptr;
}

void AMyGladiatorCharacter::Attack()
{
	if (Hammer != nullptr && Mesh != nullptr)
	{
		UMyCharacterAnimInstance* Animation = Cast<UMyCharacterAnimInstance>(Mesh->GetAnimInstance());
		if (!Animation) return;

		Animation->Attacking = true;
		Attacking = true;
		GetWorldTimerManager().SetTimer(this, &AMyGladiatorCharacter::ChangeAttack, 0.5f, false);
	}
}

void AMyGladiatorCharacter::ChangeAttack()
{
	if (Hammer != nullptr && Mesh != nullptr)
	{
		UMyCharacterAnimInstance* Animation = Cast<UMyCharacterAnimInstance>(Mesh->GetAnimInstance());
		if (!Animation) return;

		Animation->Attacking = false;
		Attacking = false;
	}
}

void AMyGladiatorCharacter::DisableCollission()
{
	DisableComponentsSimulatePhysics();
	SetActorEnableCollision(false);

	TArray<USkeletalMeshComponent*> Components;
	this->GetComponents<USkeletalMeshComponent>(Components);
	for (int32 i = 0; i < Components.Num(); i++)
	{
		USkeletalMeshComponent* StaticMeshComponent = Components[i];
		StaticMeshComponent->BodyInstance.SetResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AMyGladiatorCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	if (InputComponent)
	{
		InputComponent->BindAxis("TurnRate", this, &AMyGladiatorCharacter::TurnRate);
		InputComponent->BindAxis("LookRate", this, &AMyGladiatorCharacter::LookRate);
		InputComponent->BindAxis("MoveForward", this, &AMyGladiatorCharacter::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &AMyGladiatorCharacter::MoveRight);
		InputComponent->BindAction("Jump", IE_Pressed, this, &AMyGladiatorCharacter::Jump);
		InputComponent->BindAction("DropObject", IE_Pressed, this, &AMyGladiatorCharacter::DropWeapon);
		InputComponent->BindAction("Attack", IE_Pressed, this, &AMyGladiatorCharacter::Attack);
	}
}