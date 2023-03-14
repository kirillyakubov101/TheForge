// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IDamagable.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class AMyFPSCharacter;

UCLASS()
class FINALTERMPROJECT_API AEnemy : public ACharacter, public IDamagable
{
	GENERATED_BODY()

public:

	AEnemy();
protected:
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void UpdateHealth(float);
	virtual void DamageActor(float DamageAmount) override;

protected:

	UFUNCTION(BlueprintImplementableEvent)
		void OnDamageEvent(float damage);

	UFUNCTION(BlueprintPure)
		bool DamagePlayerEvent(float damage);

private:

	AMyFPSCharacter* Player;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		float HealthPoints = 100.f;

	void CallMyDamageEvent(float damage);
	

};
