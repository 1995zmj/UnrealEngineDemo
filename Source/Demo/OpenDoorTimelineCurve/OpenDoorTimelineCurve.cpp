// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoorTimelineCurve.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
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

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh"));
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
		TimelineFinishedCallback.BindUFunction(this, FName{ TEXT("SetState") });
		MyTimeline.AddInterpFloat(DoorCurve, TimelineCallback);
		MyTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);

		FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(this);
		float ViewportScale = UWidgetLayoutLibrary::GetViewportScale(this);
		ViewportSize.X = ViewportSize.X / ViewportScale;
		ViewportSize.Y = ViewportSize.Y / ViewportScale;
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
	TimelineValue = MyTimeline.GetPlaybackPosition();
	CurveFloatValue = RotateValue*DoorCurve->GetFloatValue(TimelineValue);

	FQuat NewRotation = FQuat(FRotator(0.f, CurveFloatValue, 0.f));

	Door->SetRelativeRotation(NewRotation);
}

void AOpenDoorTimelineCurve::SetState()
{
	ReadyState = true;
}

void AOpenDoorTimelineCurve::ToggleDoor() 
{
	if(ReadyState) 
	{
		Open = !Open;

		// alternative way to get pawn position
		// GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation()
		APawn* OurPawn = UGameplayStatics::GetPlayerPawn(this, 0);
		FVector PawnLocation = OurPawn->GetActorLocation();
		FVector Direction = GetActorLocation() - PawnLocation;
		Direction = UKismetMathLibrary::LessLess_VectorRotator(Direction, GetActorRotation());

		DoorRotation = Door->GetRelativeRotation();

		if(Open)
		{
                
			if(Direction.X > 0.0f)
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
