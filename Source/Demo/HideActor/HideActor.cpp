// Fill out your copyright notice in the Description page of Project Settings.


#include "HideActor.h"

// Sets default values
AHideActor::AHideActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHideActor::BeginPlay()
{
	Super::BeginPlay();

	if (HideInGame)
	{
		DisableActor(HideInGame);
	}
}

// Called every frame
void AHideActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHideActor::DisableActor(bool toHide)
{
	SetActorHiddenInGame(toHide);
	SetActorEnableCollision(!toHide);
	SetActorTickEnabled(!toHide);
}

