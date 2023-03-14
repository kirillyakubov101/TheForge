// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "MyFPSCharacter.h"
#include "TutorialComponent.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (Pawn != nullptr)
	{
		Player = Cast<AMyFPSCharacter>(Pawn);
		
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemySpawner::SubscribeToTutorial, 2.0f, false);
		// The above line sets a timer to call MyDelayedFunction after a delay of 1 second (1.0f)
		// The last argument (false) specifies whether the timer should repeat
	}
	
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AEnemySpawner::SubscribeToTutorial()
{
	UTutorialComponent* TutorialComp = Player->GetTutorialComponent();
	if (TutorialComp != nullptr)
	{
		TutorialComp->OnTutorialDoneDelegate.AddUObject(this, &AEnemySpawner::SpawnProcess);
	}
		
}

