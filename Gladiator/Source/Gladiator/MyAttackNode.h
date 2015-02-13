// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "MyAttackNode.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UMyAttackNode : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory);

};
