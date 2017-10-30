// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProjectileRed.generated.h"

UCLASS()
class TETHERED_API AProjectileRed : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileRed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// function to handle projectile collision
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

private:

	UStaticMeshComponent* ProjectileComponent;

	UProjectileMovementComponent* ProjectileMovement;
};
