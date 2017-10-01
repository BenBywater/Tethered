// Fill out your copyright notice in the Description page of Project Settings.

#include "Tethered.h"
#include "CableComponent.h"
#include "PlayerUFO.h"
#include "UFO1Controller.h"

AUFO1Controller::AUFO1Controller():
	UFOPawn1(NULL),
	UFOPawn2(NULL),
	Package(NULL),
	UFOSpeed(1000),
	UFO1XAxisInstance(0.f),
	UFO1YAxisInstance(0.f),
	UFO2XAxisInstance(0.f),
	UFO2YAxisInstance(0.f)
{

}
void AUFO1Controller::BeginPlay()
{
	Super::BeginPlay();
	
	FVector location = FVector(370.f, -550.f, 50.f);
	FRotator rotate = FRotator(0.f, 0.f, 0.f);
	FActorSpawnParameters SpawnInfo;
	UFOPawn1 = GetWorld()->SpawnActor<APlayerUFO>(APlayerUFO::StaticClass(), location, rotate, SpawnInfo);

	location = FVector(370.f, 750.f, 50.f);
	UFOPawn2 = GetWorld()->SpawnActor<APlayerUFO>(APlayerUFO::StaticClass(), location, rotate, SpawnInfo);
}


void AUFO1Controller::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (UFOPawn1 != NULL)
	{
		FVector PackageLocation = GetPawn()->GetActorLocation();
		// if UFO is out of leash range
		if (UFOPawn1->CalculateMovement(GetPawn() , PackageLocation))
		{
			UFOPawn1->MoveUFO();

		}
		// if UFO is out of leash range and not moving
		else if (UFO1XAxisInstance == 0 && UFO1YAxisInstance == 0)
		{
			UFOPawn1->ApplyForceToUFO(UFO1XAxisInstance, UFO1YAxisInstance, GetPawn());
		}
		// if UFO is out of leash but trying to come back
		else if (UFOPawn1->ReturnToPackage(UFO1XAxisInstance, UFO1YAxisInstance, GetPawn()))
		{
			UFOPawn1->MoveUFO();
		}
	}

	if (UFOPawn2 != NULL)
	{
		FVector PackageLocation = GetPawn()->GetActorLocation();
		if (UFOPawn2->CalculateMovement(GetPawn(), PackageLocation))
		{
			UFOPawn2->MoveUFO();
		}
		else if (UFO2XAxisInstance == 0 && UFO2YAxisInstance == 0)
		{
			UFOPawn2->ApplyForceToUFO(UFO2XAxisInstance, UFO2YAxisInstance, GetPawn());
		}
		else if (UFOPawn2->ReturnToPackage(UFO2XAxisInstance, UFO2YAxisInstance, GetPawn()))
		{
			UFOPawn2->MoveUFO();
		}
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
	if (UFOPawn1 != NULL)
	{
		UFOPawn1->SetX(Force);
		UFO1XAxisInstance = Force;
	}
}

void AUFO1Controller::MoveUFO1Y(float Force)
{
	if (UFOPawn1 != NULL)
	{
		UFOPawn1->SetY(Force);
		UFO1YAxisInstance = Force;
	}
}

void AUFO1Controller::MoveUFO2X(float Force)
{
	if (UFOPawn2 != NULL)
	{
		UFOPawn2->SetX(Force);
		UFO2XAxisInstance = Force;
	}
}

void AUFO1Controller::MoveUFO2Y(float Force)
{
	if (UFOPawn2 != NULL)
	{
		UFOPawn2->SetY(Force);
		UFO2YAxisInstance = Force;
	}
}