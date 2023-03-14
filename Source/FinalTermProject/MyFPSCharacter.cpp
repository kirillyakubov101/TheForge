// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFPSCharacter.h"
#include "TutorialComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Enemy.h"
#include "IDamagable.h"


// Sets default values
AMyFPSCharacter::AMyFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();

	//UE_LOG(LogTemp, Warning, TEXT("SUCCESS!"));

	UActorComponent* TutActor = GetComponentByClass(UTutorialComponent::StaticClass());


	if (TutActor != nullptr)
	{
		TutorialComponent = Cast< UTutorialComponent>(TutActor);
	}
}

// Called every frame
void AMyFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveF", this, &AMyFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveR", this, &AMyFPSCharacter::MoveHorizontal);
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &AMyFPSCharacter::LookHorizontal);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &AMyFPSCharacter::LookVertical);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed,this, &AMyFPSCharacter::JumpFunc);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AMyFPSCharacter::StopJumpFunc);
	PlayerInputComponent->BindAction("Dash", EInputEvent::IE_Pressed, this, &AMyFPSCharacter::DashEvent);
	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &AMyFPSCharacter::Shoot);
	
}

UTutorialComponent* AMyFPSCharacter::GetTutorialComponent() const
{
	return this->TutorialComponent;
}

void AMyFPSCharacter::DashEvent_Implementation()
{
	if (!HasDashed_Firstime) 
	{
		HasDashed_Firstime = true;
		OnDashDelegate.Broadcast();
	}
}

void AMyFPSCharacter::MoveForward(float value) 
{
	//checking for the tutorial if the player learned to move for the first time
	if (value > 0 && !HasMoved_Firstime) 
	{
		HasMoved_Firstime = true;
		OnMoveDelegate.Broadcast();
	}

	AddMovementInput(GetActorForwardVector(), value);
}

void AMyFPSCharacter::MoveHorizontal(float value)
{
	if (value > 0 && !HasMoved_Firstime)
	{
		HasMoved_Firstime = true;
		OnMoveDelegate.Broadcast();
	}
	AddMovementInput(GetActorRightVector(), value);
}

void AMyFPSCharacter::Death()
{
	DisableInput(PlayerController);
	PlayerController->bShowMouseCursor = true;
	PlayerController->SetPause(true);
	GetCharacterMovement()->DisableMovement();
	this->HealthPoints = 0.f;
	OnDeath.Broadcast();
}

void AMyFPSCharacter::JumpFunc()
{
	Jump();

	if (!HasJumped_Firstime)
	{
		HasJumped_Firstime = true;
		OnJumpDelegate.Broadcast();
	}
}

void AMyFPSCharacter::StopJumpFunc()
{
	StopJumping();
}

void AMyFPSCharacter::LookVertical(float val)
{
	if (val > 0 && !HasLooked_Firstime)
	{
		HasLooked_Firstime = true;
		OnLookDelegate.Broadcast();
	}
	AddControllerPitchInput(val);
}

void AMyFPSCharacter::LookHorizontal(float val)
{
	if (val > 0 && !HasLooked_Firstime)
	{
		HasLooked_Firstime = true;
		OnLookDelegate.Broadcast();
	}
	AddControllerYawInput(val);

}

void AMyFPSCharacter::Shoot_Implementation()
{
	if (!HasShot_Firstime)
	{
		HasShot_Firstime = true;
		OnShootDelegate.Broadcast();
	}
}

bool AMyFPSCharacter::CanDash(FVector& OutVelocity)
{
	OutVelocity = GetCharacterMovement()->Velocity;

	bool condition_1 = OutVelocity.Length() > 0.f;
	bool condition_2 = GetCharacterMovement()->IsFalling();

	return condition_1 && !condition_2;
}

void AMyFPSCharacter::LineTraceShooting(AActor*& HitActor, FVector& ImpactPoint)
{
	//the actual shooting
	FVector CameraLocation = this->PlayerController->PlayerCameraManager->GetCameraLocation();
	FRotator CameraRotation = this->PlayerController->PlayerCameraManager->GetCameraRotation();
	FVector CameraForward = CameraRotation.Vector();
	FVector EndLocation = (CameraForward * this->ShootDistance) + CameraLocation;

	// Declare a FCollisionQueryParams struct
	FCollisionQueryParams TraceParams;

	// Ignore hitting the actor that is performing the trace
	TraceParams.AddIgnoredActor(this);
	
	FHitResult Hit;
	bool hasHit = GetWorld()->LineTraceSingleByChannel
	(
		Hit,
		CameraLocation,
		EndLocation,
		TraceChannelProperty,
		TraceParams
	);

	if (hasHit)
	{
		AActor* Actor = Hit.GetActor();
		if (Actor != nullptr) 
		{
			HitActor = Actor;

			AEnemy* Enemy = Cast<AEnemy>(HitActor);

			if (Enemy != nullptr)
			{
				Enemy->DamageActor(30.f);
			}
		}

		ImpactPoint = Hit.ImpactPoint;
	}
}

void AMyFPSCharacter::DamageActor(float DamageAmount)
{
	this->HealthPoints = FMath::Max(0, HealthPoints - DamageAmount);

	if (HealthPoints <= 0.f) { IsDead = true; }
	CallReceiveDamage();
}

void AMyFPSCharacter::CallReceiveDamage()
{
	OnGetHitDelegate.Broadcast();
	ReceiveDamage();
}
