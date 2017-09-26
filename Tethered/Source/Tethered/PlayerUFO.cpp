// Fill out your copyright notice in the Description page of Project Settings.

#include "Tethered.h"
#include "PlayerUFO.h"

const FName APlayerUFO::XAxisMovementUFO1("XAxisMovementUFO1");
const FName APlayerUFO::YAxisMovementUFO1("YAxisMovementUFO1");
const FName APlayerUFO::XAxisMovementUFO2("XAxisMovementUFO2");
const FName APlayerUFO::YAxisMovementUFO2("YAxisMovementUFO2");

// Sets default values
APlayerUFO::APlayerUFO():
	XAxisValueUFO(0.f),
	YAxisValueUFO(0.f),
	UFOMeshComponent(NULL)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/UFO/TwinStickUFO"));
	// Create the mesh component
	UFOMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UFO"));
	RootComponent = UFOMeshComponent;
	UFOMeshComponent->SetSimulatePhysics(true);
	UFOMeshComponent->SetStaticMesh(ShipMesh.Object);

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
}

// Called to bind functionality to input
void APlayerUFO::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerUFO::MoveUFO()
{
	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(YAxisValueUFO, XAxisValueUFO, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate movement based on direction, speed of player and frame rate dependancy
	const FVector Movement = MoveDirection * UFOSpeed * GetWorld()->DeltaTimeSeconds;
	//UE_LOG(LogTemp, Warning, TEXT("Movement.X %f, Movement.Y %f"), Movement.X, Movement.Y);
	// If player is moving
	if (Movement.SizeSquared() > 0.0f)
	{
		//UE_LOG(LogTemp, Warning, TEXT("if (Movement.SizeSquared() > 0.0f)"));
		// calculate rotation
		const FRotator NewRotation = Movement.Rotation();
		// move player UFO
		UFOMeshComponent->MoveComponent(Movement, NewRotation, false);
	}
}

void APlayerUFO::SetX(float XAxis)
{
	XAxisValueUFO = XAxis;
}

void APlayerUFO::SetY(float YAxis)
{
	YAxisValueUFO = YAxis;
}
