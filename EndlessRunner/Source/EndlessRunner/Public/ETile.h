// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ETile.generated.h"

class UArrowComponent;
class UBoxComponent;
class AERock;

UCLASS()
class ENDLESSRUNNER_API AETile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AETile();

	UFUNCTION(BlueprintCallable, Category = "Tile")
	FTransform GetAttachmentPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile")
	USceneComponent* SceneComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile")
	UStaticMeshComponent* Floor;

	UPROPERTY(EditAnywhere, Category = "Obstacle")
	TSubclassOf<class AERock> Rock;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile")
	UStaticMeshComponent* WallLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile")
	UStaticMeshComponent* WallRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile")
	UArrowComponent* ArrowComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile")
	UArrowComponent* SpawnPoint1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile")
	UArrowComponent* SpawnPoint2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile")
	UArrowComponent* SpawnPoint3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile")
	UBoxComponent* BoxComp;

	AActor* Obstacle;

	void SpawnTile();
	void DeleteTile();

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FTimerHandle TimerHandle_DeleteTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
