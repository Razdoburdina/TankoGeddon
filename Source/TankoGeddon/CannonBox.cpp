// Fill out your copyright notice in the Description page of Project Settings.


#include "CannonBox.h"
#include "TankPawn.h"

// Sets default values
ACannonBox::ACannonBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComp;

	CannonBoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonBoxMesh"));
	CannonBoxMesh->SetupAttachment(SceneComp);
	CannonBoxMesh->OnComponentBeginOverlap.AddDynamic(this, &ACannonBox::OnMeshOverlapBegin);
	CannonBoxMesh->SetCollisionProfileName("OverlapAll");
	CannonBoxMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CannonBoxMesh->SetGenerateOverlapEvents(true);

}

void ACannonBox::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile overlap: %s"), *OtherActor->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Projectile overlap: %s"), *OtherComp->GetName());

	ATankPawn* TankPawn = Cast<ATankPawn>(OtherActor);
	if (TankPawn)
	{
		TankPawn->ChangeCannon(CannonClass);
		Destroy();
	}

}


