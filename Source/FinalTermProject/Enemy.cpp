// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "IDamagable.h"
#include "MyFPSCharacter.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//OnTakeAnyDamage.add
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	auto temp = Cast<AMyFPSCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (temp != nullptr)
	{
		Player = temp;
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::UpdateHealth(float damage)
{
	this->HealthPoints = FMath::Max(0, HealthPoints - damage);
	
	
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), HealthPoints);
}

void AEnemy::DamageActor(float damage)
{
	UpdateHealth(damage);
	CallMyDamageEvent(damage);
}

bool AEnemy::DamagePlayerEvent(float damage)
{
	if (Player == nullptr) { return false; }

	Player->DamageActor(damage);

	return true;
}

//void AEnemy::DamagePlayer(float damage)
//{
//	if (Player == nullptr) { return; }
//
//	Player->DamageActor(damage);
//}

void AEnemy::CallMyDamageEvent(float damage)
{
	OnDamageEvent(damage);
}






