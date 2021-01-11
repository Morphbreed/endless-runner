// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/ETile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Public/EGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"
#include "Public/ERock.h"
#include "Public/ECharacter.h"



// Sets default values
AETile::AETile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	Floor->SetupAttachment(RootComponent);

	WallLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallLeft"));
	WallLeft->SetupAttachment(RootComponent);

	WallRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallRight"));
	WallRight->SetupAttachment(RootComponent);

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp"));
	ArrowComp->SetupAttachment(RootComponent);

	SpawnPoint1 = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint1"));
	SpawnPoint1->SetupAttachment(RootComponent);

	SpawnPoint2 = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint2"));
	SpawnPoint2->SetupAttachment(RootComponent);

	SpawnPoint3 = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint3"));
	SpawnPoint3->SetupAttachment(RootComponent);

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AETile::OnCollision);
	BoxComp->SetupAttachment(RootComponent);
}

FTransform AETile::GetAttachmentPoint()
{
	return ArrowComp->GetComponentTransform();
}

// Called when the game starts or when spawned
void AETile::BeginPlay()
{
	Super::BeginPlay();

	if (Rock)
	{
		TArray<FTransform> SpawnLocations;
		SpawnLocations = { SpawnPoint1->GetComponentTransform(), SpawnPoint2->GetComponentTransform(), SpawnPoint3->GetComponentTransform() };
		int32 randNumber = FMath::RandRange(0, SpawnLocations.Num() - 1);

		Obstacle = GetWorld()->SpawnActor<AERock>(Rock, SpawnLocations[randNumber]);
	}

}

void AETile::SpawnTile()
{
	AEGameMode* GM = Cast<AEGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GM)
	{
		GM->SpawnTile();
	}

	GetWorldTimerManager().SetTimer(TimerHandle_DeleteTimer, this, &AETile::DeleteTile, 5.f);

}

void AETile::DeleteTile()
{
	this->Destroy();

	if (Obstacle)
	{
		Obstacle->Destroy();
	}
}


void AETile::OnCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AECharacter* Char = Cast<AECharacter>(OtherActor);

	if (Char)
	{
		SpawnTile();

	}	
}



// Called every frame
void AETile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

