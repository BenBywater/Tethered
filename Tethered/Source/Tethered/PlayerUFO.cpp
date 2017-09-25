// Fill out your copyright notice in the Description page of Project Settings.

#include "Tethered.h"
#include "PlayerUFO.h"


// Sets default values
APlayerUFO::APlayerUFO():
XAxisUFO(0.f),
YAxisUFO(0.f)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerUFO::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerUFO::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerUFO::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerUFO::MoveUFO(float xAxis, float yAxis, float deltaSeconds)
{
	XAxisUFO = xAxis;
	YAxisUFO = yAxis;

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(xAxis, yAxis, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	UE_LOG(LogTemp, Warning, TEXT("UFOSpeed = %f deltaSeconds = %f"), UFOSpeed, deltaSeconds)
	UE_LOG(LogTemp, Warning, TEXT("MoveDirection.X = %f MoveDirection.Y = %f"), MoveDirection.X, MoveDirection.Y)
	const FVector Movement = MoveDirection * UFOSpeed * deltaSeconds;
	
	const FRotator NewRotation = Movement.Rotation();
	FHitResult Hit(1.f);
	RootComponent->MoveComponent(Movement, NewRotation, false, &Hit);

}

