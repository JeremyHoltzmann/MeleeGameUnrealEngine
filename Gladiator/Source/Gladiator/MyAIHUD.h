// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "MyAIHUD.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API AMyAIHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

	virtual void DrawHUD() override;

	void DrawActorsHealth();

	void DrawHealthBar(AActor* ForActor, float HealthPercentage, int32 BarHeight, int32 OffsetY = 0);

	UPROPERTY()
	class UTexture2D* BarFillTexture;

	/** player team health bar texture */
	UPROPERTY()
	class UTexture2D* PlayerTeamHPTexture;
	
	float UIScale;
};
