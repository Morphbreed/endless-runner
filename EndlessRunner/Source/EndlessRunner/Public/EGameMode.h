// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EGameMode.generated.h"

/**
 * 
 */

UCLASS()
class ENDLESSRUNNER_API AEGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEGameMode();

protected: 
	virtual void BeginPlay() override;

	FString LastCorner;
	int Score;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	FTransform NextSpawnPoint;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AETile>> Tiles;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AETile> CornerRightTile;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AETile> CornerLeftTile;

	UFUNCTION(BlueprintCallable)
	int GetScore();

	void IncrementScore();

	UFUNCTION(BlueprintCallable)
	void SpawnTile();

	void SpawnTile(bool isInit);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowDeathNote();
};
