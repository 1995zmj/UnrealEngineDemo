// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "OpenDoorTimelineCurve.generated.h"

UCLASS()
class DEMO_API AOpenDoorTimelineCurve : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOpenDoorTimelineCurve();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Door;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* DoorFrame;

	UPROPERTY(EditAnywhere)
	UCurveFloat* DoorCurve;

	UFUNCTION()
	void ControlDoor();

	UFUNCTION()
	void ToggleDoor();

	UFUNCTION()
	void SetState();

	bool Open;
	bool ReadyState;
	float RotateValue;
	float CurveFloatValue;
	float TimelineValue;
	FRotator DoorRotation;
	FTimeline MyTimeline;
};
