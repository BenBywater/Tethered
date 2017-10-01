// Fill out your copyright notice in the Description page of Project Settings.

#include "Tethered.h"
#include <cmath> 
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "PlayerUFO.h"


// Sets default values
APlayerUFO::APlayerUFO():
	XAxisValueUFO(0.f),
	YAxisValueUFO(0.f),
	HistoricXAxis(0.f),
	HistoricYAxis(0.f),
	UFOMeshComponent(NULL),
	UFOMaterial(NULL),
	Material_Dyn(NULL)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> UFOMesh(TEXT("/Game/UFO/TwinStickUFO"));
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Game/UFO/Blue"));
	// Create the mesh component
	UFOMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UFO"));
	RootComponent = UFOMeshComponent;
	UFOMeshComponent->SetSimulatePhysics(true);
	UFOMeshComponent->SetStaticMesh(UFOMesh.Object);
	
	if (Material.Object != NULL)
	{
		UFOMaterial = (UMaterial*)Material.Object;
		Material_Dyn = UMaterialInstanceDynamic::Create(UFOMaterial, UFOMeshComponent);
		UFOMeshComponent->SetMaterial(0, Material_Dyn);
	}
	
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

void APlayerUFO::SetX(float XAxis)
{
	XAxisValueUFO = XAxis;
}

void APlayerUFO::SetY(float YAxis)
{
	YAxisValueUFO = YAxis;
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
		// calculate rotation
		const FRotator NewRotation = Movement.Rotation();
		// move player UFO
		UFOMeshComponent->MoveComponent(Movement, NewRotation, false);
		HistoricXAxis = Movement.X;
		HistoricYAxis = Movement.Y;
	}
}

bool APlayerUFO::CalculateMovement(AActor* Package, FVector PackageLocation)
{
	if (Package != NULL)
	{
		float PackageLocation = GetDistanceTo(Package);
		// If Distance is larger than leash dont move
		if (PackageLocation > UFOLeash)
		{
			return false;
		}
	}
	return true;
}

void APlayerUFO::ApplyForceToUFO(float XAxisForce, float YAxisForce, APawn* Package)
{
	// calculate Package location
	const FVector PackageLocation = Package->GetActorLocation();
	FVector Difference = (PackageLocation - GetActorLocation()).GetClampedToSize(-150.f, 150.f);
	FVector NewLocation = GetActorLocation() + Difference;
	// calculate rotation
	const FRotator CurrentRotation = UFOMeshComponent->RelativeRotation;

	// move player UFO
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(UFOMeshComponent, NewLocation, CurrentRotation, false, false, 0.2f, true, EMoveComponentAction::Type::Move, LatentInfo);
}

bool APlayerUFO::ReturnToPackage(float XAxisForce, float YAxisForce, APawn* Package)
{
	const FVector UFOLocation = GetActorLocation().GetClampedToMaxSize(1.0f);
	FVector Distance = { 0,0,0 };
	FVector NewDistance = { 0,0,0 };
	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(YAxisForce, XAxisForce, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate movement based on direction, speed of player and frame rate dependancy
	const FVector Movement = MoveDirection * UFOSpeed * GetWorld()->DeltaTimeSeconds;
	
	// Distance from UFO and Package
	Distance.Distance(UFOLocation, Package->GetActorLocation());
	// Distance to intended UFO movement and  Package
	NewDistance.Distance(Movement, Package->GetActorLocation());
	
	// If intended movement if smaller than current movement then move ufo
	if (NewDistance.Size() < Distance.Size())
	{
		return true;
	}
	else
	{
		return false;
	}
}