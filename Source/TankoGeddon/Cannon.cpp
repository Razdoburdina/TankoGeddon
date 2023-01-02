// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Projectile.h"
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
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
		if (projectile)
		{
			projectile->Start();
		}

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
		FHitResult hitResult;
		FCollisionQueryParams traceParams;
		traceParams.bTraceComplex = true;
		traceParams.bReturnPhysicalMaterial = false;

		FVector Start = ProjectileSpawnPoint->GetComponentLocation();
		FVector End = Start + ProjectileSpawnPoint->GetForwardVector() * FireRange;

		if (GetWorld()->LineTraceSingleByChannel(hitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel1, traceParams))
		{
			DrawDebugLine(GetWorld(), Start, hitResult.Location, FColor::Purple, false, 1.0f, 0, 5.0f);
			if (hitResult.GetActor())
			{
				UE_LOG(LogTemp, Warning, TEXT("trace overlap: %s"), *hitResult.GetActor()->GetName());
				hitResult.GetActor()->Destroy();

			}
		}
		else
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 5.0f);

		}
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

	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	if (projectile)
	{
		projectile->Start();
	}

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

void ACannon::AddAmmo(int32 addedAmmo)
{
	Ammo += addedAmmo;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Ammo = %i"), Ammo));
}

