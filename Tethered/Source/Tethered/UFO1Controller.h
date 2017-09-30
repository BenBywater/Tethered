// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "UFO1Controller.generated.h"

class APlayerUFO;
/**
 * 
 */
UCLASS()
class TETHERED_API AUFO1Controller : public APlayerController
{
	GENERATED_BODY()
	
public:
	AUFO1Controller();
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void SetupInputComponent() override;
	void MoveUFO1X(float Force);
	void MoveUFO1Y(float Force);
	void MoveUFO2X(float Force);
	void MoveUFO2Y(float Force);

private:
	APlayerUFO* UFOPawn1;
	APlayerUFO* UFOPawn2;
	AActor* Package;
	float UFOSpeed;
	float UFO1XAxisInstance;
	float UFO1YAxisInstance;
	float UFO2XAxisInstance;
	float UFO2YAxisInstance;
};
