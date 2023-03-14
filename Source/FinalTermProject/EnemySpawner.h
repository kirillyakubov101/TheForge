// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class AMyFPSCharacter;

UCLASS()
class FINALTERMPROJECT_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnProcess();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	void SubscribeToTutorial();

	AMyFPSCharacter* Player;
};
