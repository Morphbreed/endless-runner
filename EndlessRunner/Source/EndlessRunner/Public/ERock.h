// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ERock.generated.h"

UCLASS()
class ENDLESSRUNNER_API AERock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AERock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile")
	USceneComponent* SceneComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rock")
	UStaticMeshComponent* MeshComp;
};
