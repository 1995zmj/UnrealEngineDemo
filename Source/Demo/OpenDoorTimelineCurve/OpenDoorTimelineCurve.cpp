// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoorTimelineCurve.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TimelineComponent.h"

// Sets default values
AOpenDoorTimelineCurve::AOpenDoorTimelineCurve()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Open = false;
	ReadyState = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	RootComponent = DoorFrame;

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	Door->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AOpenDoorTimelineCurve::BeginPlay()
{
	Super::BeginPlay();
	
	RotateValue = 1.0f;

	if (DoorCurve)
	{
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;

		TimelineCallback.BindUFunction(this, FName("ControlDoor"));
		TimelineFinishedCallback.BindUFunction(this, FName(TEXT("SetState")));
		MyTimeline.AddInterpFloat(DoorCurve, TimelineCallback);
		MyTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
	}
}

// Called every frame
void AOpenDoorTimelineCurve::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MyTimeline.TickTimeline(DeltaTime);
}

void AOpenDoorTimelineCurve::ControlDoor()
{
	TimeLineValue = MyTimeline.GetPlaybackPosition();
	CurveFloatValue = RotateValue * DoorCurve->GetFloatValue(TimeLineValue);

	FQuat NewRotation = FQuat(FRotator(0.0f, CurveFloatValue, 0.0f));

	Door->SetRelativeRotation(NewRotation);
}

void AOpenDoorTimelineCurve::SetState()
{
	ReadyState = true;
}

void AOpenDoorTimelineCurve::ToggleDoor()
{
	if (ReadyState)
	{
		Open = !Open;
		DoorRotation = Door->GetRelativeRotation();

		APawn* OurPawn = UGameplayStatics::GetPlayerPawn(this, 0);
		FVector PawnLocation = OurPawn->GetActorLocation();
		FVector Direction = GetActorLocation() - PawnLocation;
		Direction = UKismetMathLibrary::LessLess_VectorRotator(Direction, GetActorRotation());

		if (Open)
		{
			if (Direction.X > 0.0f)
			{
				RotateValue = 1.0f;
			}
			else
			{
				RotateValue = -1.0f;
			}

			ReadyState = false;
			MyTimeline.PlayFromStart();
		}
		else
		{
			ReadyState = false;
			MyTimeline.Reverse();
		}
	}
}

