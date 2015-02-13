// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class GLADIATOR_API UMyCharacterAnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
		bool Attacking;
	
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
		bool Dead;
};

