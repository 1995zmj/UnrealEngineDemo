// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyActorOnOverlap.h"

#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"

// Sets default values
ADestroyActorOnOverlap::ADestroyActorOnOverlap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereRadius = 100.0f;

	MyCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MySphereComponent"));
	MyCollisionSphere->InitSphereRadius(SphereRadius);
	MyCollisionSphere->SetCollisionProfileName("Trigger");
	RootComponent = MyCollisionSphere;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	MyMesh->SetupAttachment(RootComponent);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));

	if (Asset.Succeeded())
	{
		MyMesh->SetStaticMesh(Asset.Object);
		MyMesh->SetRelativeLocation(FVector::ZeroVector);
		MyMesh->SetWorldScale3D(FVector::OneVector);
	}



	MyCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ADestroyActorOnOverlap::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ADestroyActorOnOverlap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestroyActorOnOverlap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRadius, 20, FColor::Purple, false, -1, 0, 1);
}

void ADestroyActorOnOverlap::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		Destroy();
	}
}

