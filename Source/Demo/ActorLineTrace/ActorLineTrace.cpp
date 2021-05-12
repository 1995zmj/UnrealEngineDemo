// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorLineTrace.h"
#include "UObject/ConstructorHelpers.h"
#include "DrawDebugHelpers.h"

// Sets default values
AActorLineTrace::AActorLineTrace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UStaticMeshComponent* Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	Cube->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (CubeAsset.Succeeded())
	{
		Cube->SetStaticMesh(CubeAsset.Object);
		Cube->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		Cube->SetWorldScale3D(FVector(1.0f));
	}

	TotalDamage = 200;
	DamageTimeInSeconds = 1.0f;

}

// Called when the game starts or when spawned
void AActorLineTrace::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AActorLineTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult OutHit;
	FVector Start = GetActorLocation();

	Start.Z += 50.0f;
	Start.X += 200.0f;

	FVector ForwardVector = GetActorForwardVector();
	FVector End = ((ForwardVector * 500.f) + Start);
	//FVector End = ((FVector(0.0f,0.0f,1.0f) * 500.f) + Start);
	FCollisionQueryParams CollisionParams;

	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 5);

	if (ActorLineTraceSingle(OutHit, Start, End, ECC_WorldStatic, CollisionParams))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("The Component Being Hit is: %s"), *OutHit.GetComponent()->GetName()));
	}
}

void AActorLineTrace::PostInitProperties()
{
	Super::PostInitProperties();
	//DamagePerSecond = TotalDamage / DamageTimeInSeconds;
}

void AActorLineTrace::CalculateValues()
{
	DamagePerSecond = TotalDamage / DamageTimeInSeconds;
}

void AActorLineTrace::CalledFromCpp_Implementation()
{
	// Do something cool here
}

#ifdef WITH_EDITOR
void AActorLineTrace::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	//CalculateValues();

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif