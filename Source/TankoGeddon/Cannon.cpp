// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"


ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = sceneComp;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(sceneComp);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);
}


void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();
}


void ACannon::Fire()
{
	if (!IsReadyToFire())
	{
		return;
	}

	Ammo--;

	bReadyToFire = false;

	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire projectile")));
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Ammo = %i"), Ammo));
	}

	else if (CannonType == ECannonType::FireProjectileSequence)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Ammo = %i"), Ammo));

		NumberOfSequneceShots_TEMP = NumberOfSequneceShots;
		GetWorld()->GetTimerManager().SetTimer(ShotSequenceTimer, this, &ACannon::SimpleShot, SequneceShotRate, true);
	}

	else if (CannonType == ECannonType::FireTrace)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire trace")));
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 1 / FireRate, false);

}

void ACannon::SimpleShot()
{
	if (NumberOfSequneceShots_TEMP == 0)
	{
		ShotSequenceTimer.Invalidate();
		return;
	}
	NumberOfSequneceShots_TEMP--;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire projectile sequence")));
}

void ACannon::FireSpecial()
{
	if (!IsReadyToFire())
	{
		return;
	}
	Ammo--;

	bReadyToFire = false;

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire Special")));
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Ammo = %i"), Ammo));
	

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 1 / FireRate, false);

}

void ACannon::Reload()
{
	bReadyToFire = true;
}

bool ACannon::IsReadyToFire()
{
	return (bReadyToFire && Ammo > 0);
}