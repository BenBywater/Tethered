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
	float UFOSpeed = 1000;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float UFOLeash = 800;

	void MoveUFO();

	void SetX(float x);
	void SetY(float y);

	bool CalculateMovement(AActor* Package, FVector PackageLocation);

	void ApplyForceToUFO(float XAxisForce, float YAxisForce, APawn* Package);

	float XAxisValueUFO;
	float YAxisValueUFO;
private:


	float HistoricXAxis;
	float HistoricYAxis;

	UStaticMeshComponent* UFOMeshComponent;
};
