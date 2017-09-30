// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "UFOPackage.generated.h"

class UCableComponent;

UCLASS()
class TETHERED_API AUFOPackage : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AUFOPackage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MovePackage();

private:
	UStaticMeshComponent* PackageComponent;

	UCameraComponent* Camera;

	USpringArmComponent* CameraArm;

	UCableComponent* UFOCable1;

	UCableComponent* UFOCable2;

	AActor* UFO1;
	AActor* UFO2;

	FName SockUFO1;
	FName SockUFO2;
	FName TetherEndSock;

	const float UFOLeash = 800;
};
