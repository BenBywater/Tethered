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

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveUFO(float xAxis, float yAxis, float deltaSeconds);

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float UFOSpeed;


private:
	float XAxisUFO;
	float YAxisUFO;

	
	
};
