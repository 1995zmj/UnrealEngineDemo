// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorCSV.h"

// Sets default values
AEditorCSV::AEditorCSV()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEditorCSV::BeginPlay()
{
	Super::BeginPlay();
	LoadCSV("demo");
}

// Called every frame
void AEditorCSV::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEditorCSV::LoadCSV(FString Path)
{
	FString StrPath = FPaths::ProjectSavedDir();
	UE_LOG(LogTemp,Warning,TEXT("%s"),*StrPath);
	// FString File = FPaths::ProjectContentDir() + "Configs\\" + "TestDemo";
	// FString SaveStr = "hello world";
	// FFileHelper::SaveStringToFile(SaveStr, *File);
	// if(FPaths::FileExists(Path))
	// {
	// 	FFileHelper::LoadFileToString(FileContent, *Path);
	// }
	// UE_LOG(LogTemp,Warning,TEXT("%s"),FileContent);
}

