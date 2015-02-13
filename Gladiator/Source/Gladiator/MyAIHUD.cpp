// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "MyAICharacter.h"
#include "MyAIHUD.h"


AMyAIHUD::AMyAIHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//FVector2D ViewportSize;
	//GEngine->GameViewport->GetViewportSize(ViewportSize);
	//UIScale = ViewportSize.X / 2048.0f;
	static ConstructorHelpers::FObjectFinder<UTexture2D> BarFillObj(TEXT("Texture2D'/Game/UI/HUD/BarFill.BarFill'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> PlayerTeamHPObj(TEXT("Texture2D'/Game/UI/HUD/EnemyTeamHealthBar.EnemyTeamHealthBar'"));

	BarFillTexture = BarFillObj.Object;
	PlayerTeamHPTexture = PlayerTeamHPObj.Object;

	UIScale = 0.5f;
}

void AMyAIHUD::DrawActorsHealth()
{
	for (FConstPawnIterator Iterator = GetWorld()->GetPawnIterator(); Iterator; ++Iterator)
	{
		AMyAICharacter* TestChar = Cast<AMyAICharacter>(*Iterator);
		if (TestChar != NULL && TestChar->GetHealth() > 0)
		{
			DrawHealthBar(TestChar, TestChar->GetHealth() / (float)TestChar->GetMaxHealth(), 18 * UIScale);
		}
	}
}

void AMyAIHUD::DrawHealthBar(AActor* ForActor, float HealthPercentage, int32 BarHeight, int32 OffsetY)
{
	//if (GEngine && GEngine->GameViewport)
	//{
	//	FVector2D ViewportSize;
	//	GEngine->GameViewport->GetViewportSize(ViewportSize);
	//	UIScale = ViewportSize.X / 2048.0f;
	//}
	UIScale = 1.0f;
	FBox BB = ForActor->GetComponentsBoundingBox();
	FVector Center = BB.GetCenter();
	FVector Extent = BB.GetExtent();
	FVector2D Center2D = FVector2D(Canvas->Project(FVector(Center.X, Center.Y, Center.Z + Extent.Z)));
	float ActorExtent = 40;
	if (Cast<APawn>(ForActor) != NULL)
	{
		AMyAICharacter* StrategyChar = Cast<AMyAICharacter>(ForActor);
		if ((StrategyChar != NULL) && (StrategyChar->CapsuleComponent != NULL))
		{
			ActorExtent = StrategyChar->CapsuleComponent->GetScaledCapsuleRadius();
		}
	}

	FVector Pos1 = Canvas->Project(FVector(Center.X, Center.Y - ActorExtent * 2, Center.Z + Extent.Z));
	FVector Pos2 = Canvas->Project(FVector(Center.X, Center.Y + ActorExtent * 2, Center.Z + Extent.Z));
	float HealthBarLength = (Pos2 - Pos1).Size2D();

	UTexture2D* HealthBarTexture = PlayerTeamHPTexture;

	float X = Center2D.X - HealthBarLength / 2;
	float Y = Center2D.Y + OffsetY;
	FCanvasTileItem TileItem(FVector2D(X, Y), HealthBarTexture->Resource, FVector2D(HealthBarLength * HealthPercentage, BarHeight), FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	TileItem.UV1 = FVector2D(HealthPercentage, 1.0f);


	APlayerController* Player = GetWorld()->GetFirstPlayerController();
	FRotator CameraRotation = Player->PlayerCameraManager->GetCameraRotation();
	Canvas->DrawItem(TileItem);
	//Fill the rest of health with gray gradient texture
	X = Center2D.X - HealthBarLength / 2 + HealthBarLength * HealthPercentage;
	Y = Center2D.Y + OffsetY;
	TileItem.Position = FVector2D(X, Y);
	TileItem.Rotation = CameraRotation;
	TileItem.PivotPoint = FVector2D(X, Y);
	TileItem.Texture = BarFillTexture->Resource;
	TileItem.UV1 = FVector2D(1.0f, 1.0f);
	TileItem.Size = FVector2D(HealthBarLength * (1.0f - HealthPercentage), BarHeight);
	TileItem.SetColor(FLinearColor(0.5f, 0.5f, 0.5f, 0.5f));
	Canvas->DrawItem(TileItem);
}

void AMyAIHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawActorsHealth();
}