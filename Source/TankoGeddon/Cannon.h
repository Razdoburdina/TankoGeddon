// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStruct.h"
#include "Cannon.generated.h"

UCLASS()
class TANKOGEDDON_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACannon();

	void Fire();
	void FireSpecial();
	void Reload();
	bool IsReadyToFire();
	void AddAmmo(int32 newAmmo);

	FTimerHandle ReloadTimer;
	FTimerHandle ShotSequenceTimer;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* CannonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		ECannonType CannonType = ECannonType::FireProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
		float FireRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
		float FireRange = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
		float FireDamage = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
		int32 Ammo = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
		int32 NumberOfSequneceShots = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
		float SequneceShotRate = 0.1f;

private:
	bool bReadyToFire = false;
	int32 NumberOfSequneceShots_TEMP;
	void SimpleShot();
};
