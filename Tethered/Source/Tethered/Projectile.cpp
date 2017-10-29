// Fill out your copyright notice in the Description page of Project Settings.

#include "Tethered.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile():
	ProjectileComponent(NULL),
	ProjectileMovement(NULL)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/Geometry/Meshes/Shape_Sphere.Shape_Sphere"));

	// Create mesh component for the projectile sphere
	ProjectileComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileComponent->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileComponent->SetupAttachment(RootComponent);
	// set up a notification for when this component hits something
	ProjectileComponent->BodyInstance.SetCollisionProfileName("Projectile");
	ProjectileComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);		
	RootComponent = ProjectileComponent;

	// create movement component for spawned projectile
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->UpdatedComponent = ProjectileComponent;
	ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComponent != NULL) && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
	}

	Destroy();
}