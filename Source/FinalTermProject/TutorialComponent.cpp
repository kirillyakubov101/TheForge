// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialComponent.h"
#include "MyFPSCharacter.h"

// Sets default values for this component's properties
UTutorialComponent::UTutorialComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTutorialComponent::BeginPlay()
{
	Super::BeginPlay();

	APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (Pawn != nullptr)
	{
		Player = Cast< AMyFPSCharacter>(Pawn);
		Player->OnMoveDelegate.AddUObject(this, &UTutorialComponent::TutComplete);
		Player->OnDashDelegate.AddUObject(this, &UTutorialComponent::TutComplete);
		Player->OnDashDelegate.AddUObject(this, &UTutorialComponent::TutComplete);
		Player->OnLookDelegate.AddUObject(this, &UTutorialComponent::TutComplete);
		Player->OnShootDelegate.AddUObject(this, &UTutorialComponent::TutComplete);
	}
	
}


// Called every frame
void UTutorialComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTutorialComponent::TutComplete()
{
	this->CompletedTuts++;
	if (CompletedTuts >= MUST_COMPLETE)
	{
		OnTutorialDoneDelegate.Broadcast();
		OnTutorialDoneDelegate.Clear();
		DestroyComponent();
	}
}

