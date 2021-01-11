// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/EGameMode.h"
#include "Engine/World.h"
#include "Public/ETile.h"

AEGameMode::AEGameMode()
{
	NextSpawnPoint = FTransform(FVector(0));

	LastCorner = "";
	Score = 0;


}

void AEGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i <= 3; i++)
	{
		SpawnTile(true);
	}

	for (int i = 0; i <= 7; i++)
	{
		SpawnTile();
	}
}

int AEGameMode::GetScore()
{
	return Score;
}

void AEGameMode::IncrementScore()
{
	Score++;
}

void AEGameMode::SpawnTile()
{
	if (Tiles.Num() > 0 && CornerRightTile != nullptr)
	{
		int32 randNumberDir = FMath::RandRange(0, 6);
		TSubclassOf<AETile> TileToSpawn;

		if (LastCorner == "right" && randNumberDir == 0) {
			randNumberDir = 1;
		}
		else if (LastCorner == "left" && randNumberDir == 1) {
			randNumberDir = 0;
		}

		if (randNumberDir == 0) {
			LastCorner = "right";
			TileToSpawn = CornerRightTile;
		}
		else if (randNumberDir == 1) {
			LastCorner = "left";
			TileToSpawn = CornerLeftTile;
		}
		else {
			int32 randNumberTile = FMath::RandRange(0, Tiles.Num() - 1);

			TileToSpawn = Tiles[randNumberTile];
		}

		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;

		AETile* NewTile = GetWorld()->SpawnActor<AETile>(TileToSpawn, NextSpawnPoint, spawnParams);
		NextSpawnPoint = NewTile->GetAttachmentPoint();
	}
}

void AEGameMode::SpawnTile(bool isInit)
{
	if (Tiles.Num() > 0)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;

		AETile* NewTile = GetWorld()->SpawnActor<AETile>(Tiles[0], NextSpawnPoint, spawnParams);
		NextSpawnPoint = NewTile->GetAttachmentPoint();
	}
	
}

