// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/EPickUp.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Public/ECharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Public/EGameMode.h"

// Sets default values
AEPickUp::AEPickUp()
{
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SphereComp"));
	CapsuleComp->SetupAttachment(MeshComp);
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AEPickUp::OnPickup);

	RotateComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotateComp"));
}

void AEPickUp::OnPickup(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AECharacter* Character = Cast<AECharacter>(OtherActor);

	if (Character)
	{
		AEGameMode* GM = Cast<AEGameMode>(UGameplayStatics::GetGameMode(GetWorld()));		

		if (GM)
		{
			if (PickupEffect) {
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PickupEffect, GetTransform());
			}

			if (PickupSound)
			{
				UGameplayStatics::SpawnSoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
			}

			Character->IncrementSpeed();
			GM->IncrementScore();
			this->Destroy();
		}
	}
	else {
		this->Destroy();
	}
}


