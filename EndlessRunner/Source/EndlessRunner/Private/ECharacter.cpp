// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/ECharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Public/EGameMode.h"



// Sets default values
AECharacter::AECharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmcomp"));

	CameraComp->SetupAttachment(SpringArmComp);
	SpringArmComp->SetupAttachment(RootComponent);	
}

// Called when the game starts or when spawned
void AECharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentRotation = DesiredRotation = this->GetControlRotation();		
}

// Called every frame
void AECharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddMovementInput(GetActorForwardVector() * 1);
	
	float RotationDifferenced = CurrentRotation.Yaw - DesiredRotation.Yaw;

	if (RotationDifferenced < 5 || RotationDifferenced < -5) {
		SetActorRotation(FMath::Lerp(GetActorRotation(), DesiredRotation, DeltaTime * 3));
	}
	else {
		CurrentRotation = DesiredRotation;
	}
	
}

void AECharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value * 2);
}

void AECharacter::TurnLeft()
{
	DesiredRotation.Yaw = DesiredRotation.Yaw - 90.f;	
}

void AECharacter::TurnRight()
{
	DesiredRotation.Yaw = DesiredRotation.Yaw + 90.f;	
}



void AECharacter::Die()
{
	AEGameMode* GameMode = Cast<AEGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GameMode)
	{
		GameMode->ShowDeathNote();
		bIsDead = true;

		GetMovementComponent()->StopMovementImmediately();
		GetMovementComponent()->Deactivate();

		SetLifeSpan(5.f);
	}
}

void AECharacter::IncrementSpeed()
{
	AEGameMode* GameMode = Cast<AEGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		
		int Score = GameMode->GetScore();
		float MaxSpeed = GetCharacterMovement()->MaxWalkSpeed;
		GetCharacterMovement()->MaxWalkSpeed = MaxSpeed + Score;
	}

	UE_LOG(LogTemp, Warning, TEXT("Current Speed: %f"), GetCharacterMovement()->MaxWalkSpeed);
}

// Called to bind functionality to input
void AECharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveRight", this, &AECharacter::MoveRight);

	PlayerInputComponent->BindAction("turnLeft", IE_Pressed, this, &AECharacter::TurnLeft);

	PlayerInputComponent->BindAction("TurnRight", IE_Pressed, this, &AECharacter::TurnRight);
}

