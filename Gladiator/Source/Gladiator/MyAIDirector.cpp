// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "MyAIDirector.h"
#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


AMyAIDirector::AMyAIDirector(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP), DeltaAttack(2), CurrentAI(0), AIClassToSpawn(nullptr)
{

}


void AMyAIDirector::BeginPlay()
{
	Super::BeginPlay();

	SpawnedAIArray.SetNum(SpawnPointArray.Num());
	for (int i = 0; i < SpawnPointArray.Num(); ++i)
	{
		AActor*	SpawnPoint = SpawnPointArray[i];
		if (SpawnPoint != nullptr)
		{
			FVector SpawnLocation = SpawnPoint->GetActorLocation();
			FRotator SpawnRotation = SpawnPoint->GetActorRotation();

			APawn* AIPawn = Cast<APawn>(GetWorld()->SpawnActor(AIClassToSpawn, &SpawnLocation, &SpawnRotation));
			SpawnedAIArray[i] = AIPawn;
			if (AIPawn != nullptr)
			{
				AIPawn->SpawnDefaultController();
				AController* Controller = AIPawn->GetController();
				((AMyGladiatorCharacter*)Controller)->MaxPV = EnemyPV;
				if (Controller != nullptr)
				{
					UBlackboardComponent* BlackBoardComp = Controller->FindComponentByClass<UBlackboardComponent>();
					if (BlackBoardComp != nullptr)
					{
						BlackBoardComp->SetValueAsObject("Player", UGameplayStatics::GetPlayerCharacter(this, 0));
					}
				}
			}
		}
	}
	GetWorldTimerManager().SetTimer(this, &AMyAIDirector::ChangeAttacker, DeltaAttack, true);
	GetWorldTimerManager().SetTimer(this, &AMyAIDirector::ChangeEnemyPosition, 0.1f, true);
}

void AMyAIDirector::ChangeEnemyPosition()
{
	float rotation = 2 * PI / SpawnedAIArray.Num();
	for (int i = 0; i < SpawnedAIArray.Num(); i++)
	{
		SpawnedAIArray[i]->SpawnDefaultController();
		AController* Controller = SpawnedAIArray[i]->GetController();
		((AMyGladiatorCharacter*)Controller)->MaxPV = EnemyPV;
		if (Controller != nullptr)
		{
			UBlackboardComponent* BlackBoardComp = Controller->FindComponentByClass<UBlackboardComponent>();
			if (BlackBoardComp != nullptr)
			{
				ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
				FVector Position;
				float actorRotation = i * rotation;
				Position.X = Player->GetActorLocation().X + (600 * FMath::Cos(actorRotation));
				Position.Y = Player->GetActorLocation().X + (600 * FMath::Sin(actorRotation));
				Position.Z = 0;
				BlackBoardComp->SetValueAsVector("MovePoint", Position);
			}
		}
	}
}

void AMyAIDirector::ToggleAttacker(int attacker, bool toSet)
{
	AController* Controller = SpawnedAIArray[attacker]->GetController();
	if (Controller != nullptr)
	{
		UBlackboardComponent* BlackBoardComp = Controller->FindComponentByClass<UBlackboardComponent>();
		if (BlackBoardComp != nullptr)
		{
			BlackBoardComp->SetValueAsBool("Attack", toSet);
		}
	}
}

void AMyAIDirector::ChangeAttacker()
{
	if (SpawnedAIArray.Num() == 1)
		return;
	int rand =  FMath::RandRange(0, SpawnedAIArray.Num() - 1);;
	while (rand  == CurrentAI)
		rand = FMath::RandRange(0, SpawnedAIArray.Num() - 1);
	ToggleAttacker(rand, true);
	ToggleAttacker(CurrentAI, false);
	CurrentAI = rand;
}