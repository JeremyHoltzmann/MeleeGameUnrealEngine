// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MyAICharacter.h"
#include "MyAIDirector.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API AMyAIDirector : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Director)
	UClass*	AIClassToSpawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Director)
	TArray<AActor*>	SpawnPointArray;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Director)
	TArray<APawn*>	SpawnedAIArray;                                                                                                                                                                            
	
	UPROPERTY(BlueprintReadWrite, Editanywhere, Category = Director)
	float	DeltaAttack;

	UPROPERTY(BlueprintReadWrite, Editanywhere, Category = Director)
	float	EnemyPV;

	int CurrentAI;

	virtual void BeginPlay() override;
	void ChangeAttacker();
	void ToggleAttacker(int, bool);

	void ChangeEnemyPosition();
};
