// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "Characters/MyGladiatorCharacter.h"
#include "MyAIHUD.h"
#include "GladiatorGameMode.h"


AGladiatorGameMode::AGladiatorGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP), HeroPV(5)
{

	static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerPawnObject(TEXT("Blueprint'/Game/Blueprints/MyGladiatorBluePrint.MyGladiatorBluePrint'"));
	if (PlayerPawnObject.Object != NULL)
	{
		DefaultPawnClass = (UClass*)PlayerPawnObject.Object->GeneratedClass;
	}
	static ConstructorHelpers::FObjectFinder<UBlueprint> HUDObject(TEXT("Blueprint'/Game/HUD/MyHUDBP.MyHUDBP'"));
	if (HUDObject.Object != nullptr)
	{
		HUDClass = (UClass*)HUDObject.Object->GeneratedClass;
	}

	
}

void AGladiatorGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		//GEngine->AddOnScreenDebug(-1, 5.f, FColor::Blue, TEXT("We are using FPSCharacter!"));	
	}
	((AMyGladiatorCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0))->PV = HeroPV;
}


