// Fill out your copyright notice in the Description page of Project Settings.

#include "Tethered.h"
#include "PlayerUFO.h"
#include "UFO1Controller.h"

void AUFO1Controller::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("UFO1Controller Class"));
	
	
	FVector location = FVector(370.f, -550.f, 50.f);
	FRotator rotate = FRotator(0.f, 0.f, 0.f);
	FActorSpawnParameters SpawnInfo;
	ufoPawn1 = GetWorld()->SpawnActor<APlayerUFO>(APlayerUFO::StaticClass(), location, rotate, SpawnInfo);

	location = FVector(370.f, 750.f, 50.f);
	ufoPawn2 = GetWorld()->SpawnActor<APlayerUFO>(APlayerUFO::StaticClass(), location, rotate, SpawnInfo);
}


void AUFO1Controller::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (ufoPawn1 != NULL)
	{
		ufoPawn1->MoveUFO();
	}

	if (ufoPawn2 != NULL)
	{
		ufoPawn2->MoveUFO();
	}
	
}

void AUFO1Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("XAxisMovementUFO1", this, &AUFO1Controller::MoveUFO1X);
	InputComponent->BindAxis("YAxisMovementUFO1", this, &AUFO1Controller::MoveUFO1Y);

	InputComponent->BindAxis("XAxisMovementUFO2", this, &AUFO1Controller::MoveUFO2X);
	InputComponent->BindAxis("YAxisMovementUFO2", this, &AUFO1Controller::MoveUFO2Y);
}

void AUFO1Controller::MoveUFO1X(float Force)
{
	if (ufoPawn1 != NULL)
	{
		
		ufoPawn1->SetX(Force);
	}
}

void AUFO1Controller::MoveUFO1Y(float Force)
{
	if (ufoPawn1 != NULL)
	{
		ufoPawn1->SetY(Force);
	}
}

void AUFO1Controller::MoveUFO2X(float Force)
{
	if (ufoPawn2 != NULL)
	{

		ufoPawn2->SetX(Force);
	}
}

void AUFO1Controller::MoveUFO2Y(float Force)
{
	if (ufoPawn2 != NULL)
	{
		ufoPawn2->SetY(Force);
	}
}