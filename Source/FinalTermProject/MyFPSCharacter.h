// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IDamagable.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyFPSCharacter.generated.h"


class UTutorialComponent;

// Delegate signature
DECLARE_MULTICAST_DELEGATE(FOnMoveSingnature)
DECLARE_MULTICAST_DELEGATE(FOnDashSingnature)
DECLARE_MULTICAST_DELEGATE(FOnLookSingnature)
DECLARE_MULTICAST_DELEGATE(FOnShootSingnature)
DECLARE_MULTICAST_DELEGATE(FOnJumpSingnature)
DECLARE_MULTICAST_DELEGATE(FOnDeathSingnature)
DECLARE_MULTICAST_DELEGATE(FOnGetHitSingnature)

UCLASS()
class FINALTERMPROJECT_API AMyFPSCharacter : public ACharacter, public IDamagable
{
	GENERATED_BODY()

		

public:
	// Sets default values for this character's properties
	AMyFPSCharacter();

	FOnMoveSingnature OnMoveDelegate;
	FOnDashSingnature OnDashDelegate;
	FOnLookSingnature OnLookDelegate;
	FOnShootSingnature OnShootDelegate;
	FOnJumpSingnature OnJumpDelegate;
	FOnDeathSingnature OnDeath;
	FOnGetHitSingnature OnGetHitDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UTutorialComponent* GetTutorialComponent() const;

	virtual void DamageActor(float DamageAmount) override;

protected:

	UFUNCTION(BlueprintNativeEvent)
	void DashEvent();

	UFUNCTION(BlueprintNativeEvent)
	void Shoot();

	UFUNCTION(BlueprintImplementableEvent)
		void ReceiveDamage();

	UFUNCTION(BlueprintCallable)
	void LineTraceShooting(AActor*& HitActor,FVector& ImpactPoint);

private:
	UFUNCTION(BlueprintPure, Category = "Dashing")
	bool CanDash(FVector& OutVelocity);

	UFUNCTION(BlueprintCallable, Category = "Death")
	void Death();

	void CallReceiveDamage();

	UFUNCTION(BlueprintPure)
	bool IsPlayerDead() const 
	{
		return IsDead;
	}

private:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Launch Stats", meta = (AllowPrivateAccess = "true"))
		float Launch_Z_Force = 200.f;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Launch Stats", meta = (AllowPrivateAccess = "true"))
		float Launch_Z_ForceMultiplier = 800.f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))
		float HealthPoints = 100.f;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Shooting", meta = (AllowPrivateAccess = "true"))
		float ShootDistance = 10000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
		TEnumAsByte<ECollisionChannel> TraceChannelProperty;

	APlayerController* PlayerController;
	UTutorialComponent* TutorialComponent;

	void MoveForward(float);
	void MoveHorizontal(float);
	void JumpFunc();
	void StopJumpFunc();
	void LookVertical(float);
	void LookHorizontal(float);



	//tutorial states
	bool HasMoved_Firstime = false;
	bool HasLooked_Firstime = false;
	bool HasJumped_Firstime = false;
	bool HasDashed_Firstime = false;
	bool HasShot_Firstime = false;
	bool IsDead = false;
};
