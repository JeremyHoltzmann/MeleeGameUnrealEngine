// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "MyAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "MyAICharacter.h"


AMyAICharacter::AMyAICharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent"))), BT(nullptr)
{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		static ConstructorHelpers::FObjectFinder<UBehaviorTree> ItemBlueprint(TEXT("BehaviorTree'/Game/AI/MyBT.MyBT'"));
		if (ItemBlueprint.Object)
			BT = (UBehaviorTree*)ItemBlueprint.Object;
	}
	PrimaryActorTick.bCanEverTick = true;
}

void AMyAICharacter::Tick(float DeltaSecond)
{
	UBlackboardComponent* BlackBoardComp = Controller->FindComponentByClass<UBlackboardComponent>();
	if (BlackBoardComp == nullptr) return;
	Super::Tick(DeltaSecond);
	if (PV == 1 && !BlackBoardComp->GetValueAsBool("RunningAway"))
	{
		BlackBoardComp->SetValueAsBool("RunningAway", true);
		GetWorldTimerManager().SetTimer(this, &AMyAICharacter::ChangeRunningPoint, 1.0f, true);
		DropWeapon();
	}
}
void AMyAICharacter::ChangeRunningPoint()
{
	UBlackboardComponent* BlackBoardComp = Controller->FindComponentByClass<UBlackboardComponent>();
	if (BlackBoardComp)
	{
		FVector runningPoint = BlackBoardComp->GetValueAsVector("RunningPoint");
		
		runningPoint = GetActorLocation() + FVector(FMath::RandRange(-500, 500), FMath::RandRange(-500, 500), 0);
		BlackBoardComp->SetValueAsVector("RunningPoint", runningPoint);
	}
}

void AMyAICharacter::BeginPlay()
{
	Super::BeginPlay();
	AAIController* AiController = CastChecked<AAIController>(Controller);
	if (BT != nullptr && AiController != nullptr)
	{
		AiController->RunBehaviorTree(BT);
		UBlackboardComponent* BlackBoardComp = AiController->FindComponentByClass<UBlackboardComponent>();
		if (BlackBoardComp != nullptr)
		{
			BlackBoardComp->SetValueAsObject("Player", UGameplayStatics::GetPlayerCharacter(this, 0));
		}
	}
}

void AMyAICharacter::IsDead()
{
	Super::IsDead();
	//PrimaryActorTick.bCanEverTick = false;
	//Controller->Destroy();
}