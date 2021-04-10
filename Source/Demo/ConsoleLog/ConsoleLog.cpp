// Fill out your copyright notice in the Description page of Project Settings.

// define a print message function to print to screen
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT(text), fstring))
#include "ConsoleLog.h"

// Sets default values
AConsoleLog::AConsoleLog()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AConsoleLog::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("I just started running"));

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Screen Message"));

	FVector myVector = FVector(200, 100, 900);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("My Location is: %s"), *GetActorLocation().ToString()));

	print("hello unreal");

	printFString("My Variable Vector is: %s", *myVector.ToString());
}

// Called every frame
void AConsoleLog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

