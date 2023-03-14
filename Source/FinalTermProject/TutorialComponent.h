// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TutorialComponent.generated.h"

class AMyFPSCharacter;

DECLARE_MULTICAST_DELEGATE(FOnTutorialDoneSingnature)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FINALTERMPROJECT_API UTutorialComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTutorialComponent();

	FOnTutorialDoneSingnature OnTutorialDoneDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	

private:
	void TutComplete();


	int CompletedTuts = 0;
	const int MUST_COMPLETE = 5;

	AMyFPSCharacter* Player;
};
