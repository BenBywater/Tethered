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
		//UFOPawn1->MoveUFO();
		FVector PackageLocation = GetPawn()->GetActorLocation();
		if (UFOPawn1->CalculateMovement(GetPawn() , PackageLocation))
		{
			UFOPawn1->MoveUFO();

		}
		else
		{
			UFOPawn1->ApplyForceToUFO(UFO2XAxisInstance, UFO2YAxisInstance);
		}
		
		//else
		//{
		//	const FVector MoveDirection = FVector(UFOPawn1->YAxisValueUFO, UFOPawn1->XAxisValueUFO, 0.f).GetClampedToMaxSize(1.0f);
		//	UE_LOG(LogTemp, Warning, TEXT("UFOPawn1->YAxisValueUFO %f UFOPawn1->XAxisValueUFO %f"), UFOPawn1->XAxisValueUFO, UFOPawn1->YAxisValueUFO);
		//	const FVector Movement = MoveDirection * UFOSpeed * GetWorld()->DeltaTimeSeconds;

		//	if (Movement.SizeSquared() > 0.0f)
		//	{
		//		// calculate rotation
		//		const FRotator NewRotation = Movement.Rotation();
		//		// move player UFO
		//		RootComponent->MoveComponent(Movement, NewRotation, false);
		//		
		//		UE_LOG(LogTemp, Warning, TEXT("Movement.X %f Movement.Y %f"), Movement.X, Movement.Y);
		//	}
		//}
	}

	if (UFOPawn2 != NULL)
	{
		FVector PackageLocation = GetPawn()->GetActorLocation();
		if (UFOPawn2->CalculateMovement(GetPawn(), PackageLocation))
		{
			UFOPawn2->MoveUFO();
		}
		else
		{
			UFOPawn2->ApplyForceToUFO(UFO1XAxisInstance, UFO1YAxisInstance, GetPawn());
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