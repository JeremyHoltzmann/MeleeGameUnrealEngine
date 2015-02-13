// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "MyAIController.h"
#include "Characters/MyGladiatorCharacter.h"
#include "MyAttackNode.h"


UMyAttackNode::UMyAttackNode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

EBTNodeResult::Type UMyAttackNode::ExecuteTask(UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* MyComp = OwnerComp;
	UBlackboardComponent* BTC = MyComp->GetBlackboardComponent();

	AAIController* controller = Cast<AAIController>(OwnerComp->GetOwner());

	if (controller)
	{
		APawn* Pawn = controller->GetCharacter();
		if (Pawn)
		{
			AMyGladiatorCharacter* gladiatarComponent = Cast<AMyGladiatorCharacter>(Pawn);
			if (gladiatarComponent)
				gladiatarComponent->Attack();
		}
	}


	return EBTNodeResult::Succeeded;
}
