// Fill out your copyright notice in the Description page of Project Settings.

#include "Tethered.h"
#include "PlayerUFO.h"

const FName APlayerUFO::XAxisMovementUFO1("XAxisMovementUFO1");
const FName APlayerUFO::YAxisMovementUFO1("YAxisMovementUFO1");
const FName APlayerUFO::XAxisMovementUFO2("XAxisMovementUFO2");
const FName APlayerUFO::YAxisMovementUFO2("YAxisMovementUFO2");

// Sets default values
APlayerUFO::APlayerUFO():
	XAxisValue(0.f),
	YAxisValue(0.f)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerUFO::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("MyName is %s"), *GetName());
}

// Called every frame
void APlayerUFO::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (GetName().Contains("UFO1"))
	{
		XAxisValue = GetInputAxisValue(XAxisMovementUFO1);
		YAxisValue = GetInputAxisValue(YAxisMovementUFO1);
		MoveUFO(XAxisValue, YAxisValue, DeltaTime);
	}
	else if (GetName().Contains("UFO2"))
	{
		XAxisValue = GetInputAxisValue(XAxisMovementUFO2);
		YAxisValue = GetInputAxisValue(YAxisMovementUFO2);
		MoveUFO(XAxisValue, YAxisValue, DeltaTime);
	}
}

// Called to bind functionality to input
void APlayerUFO::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Bind player inputs
	if (PlayerInputComponent != NULL)
	{
		PlayerInputComponent->BindAxis(XAxisMovementUFO1);
		PlayerInputComponent->BindAxis(YAxisMovementUFO1);
		PlayerInputComponent->BindAxis(XAxisMovementUFO2);
		PlayerInputComponent->BindAxis(YAxisMovementUFO2);
	}
}

void APlayerUFO::MoveUFO(float XAxis, float YAxis, float DeltaTime)
{
	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(YAxisValue, XAxisValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate movement based on direction, speed of player and frame rate dependancy
	const FVector Movement = MoveDirection * UFOSpeed * DeltaTime;

	// If player is moving
	if (Movement.SizeSquared() > 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Movement.X = %f Movement.Y = %f"), Movement.X, Movement.Y);
		// calculate rotation
		const FRotator NewRotation = Movement.Rotation();
		// move player UFO
		RootComponent->MoveComponent(Movement, NewRotation, false);
	}
}