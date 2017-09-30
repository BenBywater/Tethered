// Fill out your copyright notice in the Description page of Project Settings.

#include "Tethered.h"
#include "CableComponent.h"
#include "PlayerUFO.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "UFOPackage.h"


// Sets default values
AUFOPackage::AUFOPackage():
	PackageComponent(NULL),
	CameraArm(NULL),
	Camera(NULL),
	UFOCable1(NULL),
	UFOCable2(NULL),
	UFO1(NULL),
	UFO2(NULL),
	SockUFO1("TetherUFO1"),
	SockUFO2("TetherUFO2"),
	TetherEndSock("TetherEnd")
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PackageMesh(TEXT("/Game/Geometry/Meshes/1M_Cube"));
	// Create the mesh component
	PackageComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Package"));
	RootComponent = PackageComponent;
	PackageComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	PackageComponent->SetStaticMesh(PackageMesh.Object);
	PackageComponent->SetSimulatePhysics(true);
	PackageComponent->SetLinearDamping(0.01);
	PackageComponent->SetEnableGravity(true);
	
	// Create a camera arm
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->bAbsoluteRotation = true; // Don't want arm to rotate when ship does
	CameraArm->TargetArmLength = 1500.f;
	CameraArm->RelativeRotation = FRotator(-80.f, 0.f, 0.f);
	CameraArm->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	UFOCable1 = CreateDefaultSubobject<UCableComponent>(TEXT("CableUFO1"));
	UFOCable1->SetupAttachment(PackageComponent, SockUFO1);

	UFOCable2 = CreateDefaultSubobject<UCableComponent>(TEXT("CableUFO2"));
	UFOCable2->SetupAttachment(PackageComponent, SockUFO2);
}

// Called when the game starts or when spawned
void AUFOPackage::BeginPlay()
{
	Super::BeginPlay();
	
	// collect UFO actors already created by Player Controller
	TArray<AActor*> UFOActors;
	TSubclassOf<APlayerUFO> PlayerUFOClass = APlayerUFO::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerUFOClass, UFOActors);

	UFO1 = UFOActors[0];
	UFO2 = UFOActors[1];

	// create lambda function for actor arracy and cable array
	UFOCable1->SetAttachEndTo(UFO1, "", TetherEndSock);
	UFOCable2->SetAttachEndTo(UFO2, "", TetherEndSock);
}

// Called every frame
void AUFOPackage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FRotator NewRotation = { 0,0,0 };
	PackageComponent->SetRelativeRotation(NewRotation, false, NULL, ETeleportType::None);
	MovePackage();

}

// Called to bind functionality to input
void AUFOPackage::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AUFOPackage::MovePackage()
{
	// calculate distances between UFO actors and Package
	float DistanceUFO1 = GetDistanceTo(UFO1);
	float DistanceUFO2 = GetDistanceTo(UFO2);
	float Distance = 0;
	FVector UFOLocation;
	// Get furthest UFO Location
	if (DistanceUFO1 > DistanceUFO2)
	{
		UFOLocation = UFO1->GetActorLocation();
		Distance = DistanceUFO1;
	}
	else
	{
		UFOLocation = UFO2->GetActorLocation();
     	Distance = DistanceUFO2;
	}

	if (Distance > UFOLeash)
	{
		FVector PackageLocation = GetActorLocation();
		// Find difference between Package and UFO
		FVector Difference = (UFOLocation - PackageLocation).GetClampedToSize2D(-120.f, 120.f);
		PackageLocation += Difference;

		// calculate rotation
		const FRotator NewRotation = PackageLocation.Rotation();
		// move player UFO
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		UKismetSystemLibrary::MoveComponentTo(PackageComponent, PackageLocation, NewRotation, false, false, 0.2f, true, EMoveComponentAction::Type::Move, LatentInfo);
	}
}