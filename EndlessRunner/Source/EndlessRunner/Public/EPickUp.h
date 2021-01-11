// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EPickUp.generated.h"

class UCapsuleComponent;
class URotatingMovementComponent;

UCLASS()
class ENDLESSRUNNER_API AEPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEPickUp();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUp")
	USceneComponent* SceneComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUp")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUp")
	UCapsuleComponent* CapsuleComp;

	URotatingMovementComponent* RotateComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
	UParticleSystem* PickupEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
	USoundBase* PickupSound;

	UFUNCTION()
	void OnPickup(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
