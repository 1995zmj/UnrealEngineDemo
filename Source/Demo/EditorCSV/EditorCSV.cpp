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
	FString str = LoadCSV(TEXT("demo.csv"));
	UE_LOG(LogTemp,Warning,TEXT("%s"),*str);
	
	// FString str = FileContent, leftstr, rightstr;
	//
	// while (str.Split(TEXT("\r\n"), &leftstr, &rightstr))
 //    	{
 //    		lineStr.Emplace(leftstr);
 //    		str = rightstr;
	// 	
 //    	}

	// FString JsonValue = "[{\"author\":\"4446545646544\"},{\"name\":\"jack\"}]";  
 //      
	// FString JsonStr;  
	// TArray<TSharedPtr<FJsonValue>> JsonParsed;  
	// TSharedRef< TJsonReader<TCHAR> > JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);     
 //          
	// bool BFlag = FJsonSerializer::Deserialize(JsonReader, JsonParsed);  
	// if (BFlag)  
	// {  
	// 	int ArrayNumber = JsonParsed.Num();  
	// 	if (ArrayNumber == 2)  
	// 	{  
	// 		FString FStringAuthor = JsonParsed[0]->AsObject()->GetStringField("author");  
	// 		if (GEngine)  
	// 		{  
	// 			FString TmpString = "author :" + FStringAuthor;  
	// 			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TmpString);  
	// 		}  
	// 		FString FStringName = JsonParsed[1]->AsObject()->GetStringField("name");  
	// 		if (GEngine)  
	// 		{  
	// 			FString TmpString = "name :" + FStringName;  
	// 			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TmpString);  
	// 		}  
	// 	}  
	// }
	
}

// Called every frame
void AEditorCSV::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AEditorCSV::LoadCSV(FString FileName)
{


	
	FString Grades = "test";
	TArray<FString> Name;
	Name.Add("zhangsan");
	Name.Add("lisi");
	Name.Add("wangwu");
 
	FString JsonOutString;
	TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer = TJsonWriterFactory< TCHAR, TCondensedJsonPrintPolicy<TCHAR> >::Create(&JsonOutString);
 
	Writer->WriteObjectStart();            
	Writer->WriteValue(L"grades", Grades);   
	Writer->WriteValue(L"member", Name); //普通数组
	Writer->WriteObjectEnd();             
	Writer->Close();

	
	FString StrPath = FPaths::ProjectSavedDir();
	FString File = FPaths::ProjectContentDir() + "Configs/" + FileName;
	FString ContentStr = "";
	if(FPaths::FileExists(File))
	{
		FFileHelper::LoadFileToString(ContentStr, *File);
	}
	return ContentStr;
}

void AEditorCSV::SaveCSV(FString FileName,FString SaveStr)
{
	FString StrPath = FPaths::ProjectSavedDir();
	FString File = FPaths::ProjectContentDir() + "Configs/" + FileName;
	FFileHelper::SaveStringToFile(SaveStr, *File);
}

