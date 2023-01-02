// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoBox.h"
#include "TankPawn.h"


// Sets default values
AAmmoBox::AAmmoBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComp;

	AmmoBoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoBoxMesh"));
	AmmoBoxMesh->SetupAttachment(SceneComp);
	AmmoBoxMesh->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnMeshOverlapBegin);
	AmmoBoxMesh->SetCollisionProfileName("OverlapAll");
	AmmoBoxMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AmmoBoxMesh->SetGenerateOverlapEvents(true);

}

void AAmmoBox::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile overlap: %s"), *OtherActor->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Projectile overlap: %s"), *OtherComp->GetName());

	ATankPawn* TankPawn = Cast<ATankPawn>(OtherActor);
	if (TankPawn)
	{

		TankPawn->AddAmmo(Ammo);
		Destroy();
	}
}

