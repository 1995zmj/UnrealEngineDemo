// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingActor.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UStaticMeshComponent* meshCom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	RootComponent = meshCom;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));
	if (MeshAsset.Succeeded())
	{
		meshCom->SetStaticMesh(MeshAsset.Object);
		meshCom->SetRelativeLocation(FVector::ZeroVector);
		meshCom->SetWorldScale3D(FVector(1.0f));
	}
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.X += DeltaHeight * XValue;
	NewLocation.Y += DeltaHeight * YValue;
	NewLocation.Z += DeltaHeight * ZValue;

	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}

