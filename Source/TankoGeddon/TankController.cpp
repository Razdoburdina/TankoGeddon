// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"
#include "TankPawn.h"
#include "DrawDebughelpers.h"

ATankController::ATankController()
{
	bShowMouseCursor = true; 
}

void ATankController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	TankPawn = Cast<ATankPawn>(InPawn);
}

void ATankController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &ATankController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATankController::MoveRight);
	InputComponent->BindAxis("RotateRight", this, &ATankController::RotateRight);
	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ATankController::Fire);
	InputComponent->BindAction("FireSpecial", EInputEvent::IE_Pressed, this, &ATankController::FireSpecial);
	InputComponent->BindAction("SwitchCannon", EInputEvent::IE_Pressed, this, &ATankController::SwitchCannon);

}

void ATankController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (TankPawn)
	{
	FVector MouseDirection;
	DeprojectMousePositionToWorld(MousePos, MouseDirection);
	FVector tankPosition = TankPawn->GetActorLocation();
	MousePos.Z = tankPosition.Z;
	FVector dir = MousePos - tankPosition;
	dir.Normalize();
	MousePos = tankPosition + dir * 1000.0f;
	DrawDebugLine(GetWorld(), tankPosition, MousePos, FColor::Green, false, 0.1f, 0, 5);
	} 

}

void ATankController::MoveForward(float Value)
{
	if (TankPawn)
	{
		TankPawn->MoveForward(Value);
	}
}

void ATankController::MoveRight(float Value)
{
	if (TankPawn)
	{
		TankPawn->MoveRight(Value);
	}
}

void ATankController::RotateRight(float Value)
{
	if (TankPawn)
	{
		TankPawn->RotateRight(Value);
	}
}

void ATankController::Fire()
{
	if (TankPawn)
	{
		TankPawn->Fire();
	}
}

void ATankController::FireSpecial()
{
	if (TankPawn)
	{
		TankPawn->FireSpecial();
	}
}

void ATankController::SwitchCannon()
{
	if (TankPawn)
	{
		TankPawn->SwitchCannon();
	}
}
