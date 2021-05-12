// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorLineTrace.generated.h"

UCLASS()
class DEMO_API AActorLineTrace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorLineTrace();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 TotalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageTimeInSeconds;
	 
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "Damage")
	float DamagePerSecond;

	virtual void PostInitProperties() override;

#ifdef WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, Category = "Damage")
	void CalledFromCpp();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void CalculateValues();

};
