// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "GladiatorGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API AGladiatorGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	int32 HeroPV;

	void AGladiatorGameMode::BeginPlay() override;
};
