// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "PlayerUFO.generated.h"

UCLASS()
class TETHERED_API APlayerUFO : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerUFO();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float UFOSpeed;

	void MoveUFO(float XAxis, float YAxis, float DeltaTime);

	static const FName XAxisMovementUFO1;
	static const FName YAxisMovementUFO1;
	static const FName XAxisMovementUFO2;
	static const FName YAxisMovementUFO2;

private:
	float XAxisValue;
	float YAxisValue;

	
};
