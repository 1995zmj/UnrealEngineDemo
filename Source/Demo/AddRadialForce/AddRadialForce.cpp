// Fill out your copyright notice in the Description page of Project Settings.


#include "AddRadialForce.h"
#include "DrawDebugHelpers.h"

// Sets default values
AAddRadialForce::AAddRadialForce()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAddRadialForce::BeginPlay()
{
	Super::BeginPlay();
	TArray<FHitResult> OutHits;

	FVector MyLocation = GetActorLocation();

	FVector Start = MyLocation;
	FVector End = MyLocation;

	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(500.0f);

	DrawDebugSphere(GetWorld(), GetActorLocation(), MyColSphere.GetSphereRadius(), 50, FColor::Cyan, true);

	bool isHit = GetWorld()->SweepMultiByChannel(OutHits, Start, End, FQuat::Identity, ECC_WorldStatic, MyColSphere);

	if (isHit)
	{
		for (auto& Hit : OutHits)
		{
			UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>((Hit.GetActor())->GetRootComponent());

			if (MeshComp)
			{
				MeshComp->AddRadialImpulse(GetActorLocation(), 500.0f, 2000.0f, ERadialImpulseFalloff::RIF_Constant, true);
			}
		}
	}
}

// Called every frame
void AAddRadialForce::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

