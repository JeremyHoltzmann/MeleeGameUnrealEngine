// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Characters/MyGladiatorCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "MyAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API AMyAICharacter : public AMyGladiatorCharacter
{
	GENERATED_UCLASS_BODY()

	virtual void BeginPlay() override;
	virtual void IsDead() override;

	UBehaviorTree* BT;

	virtual void Tick(float DeltaSecondOverride) override;
	void ChangeRunningPoint();
};
