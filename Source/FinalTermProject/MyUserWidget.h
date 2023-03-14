// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"


class AMyFPSCharacter;
/**
 * 
 */
UCLASS()
class FINALTERMPROJECT_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:

	UFUNCTION(BlueprintImplementableEvent)
		void MoveDone();

	UFUNCTION(BlueprintImplementableEvent)
		void DashDone();

	UFUNCTION(BlueprintImplementableEvent)
		void JumpDone();

	UFUNCTION(BlueprintImplementableEvent)
		void LookDone();

	UFUNCTION(BlueprintImplementableEvent)
		void ShootDone();

	UFUNCTION(BlueprintImplementableEvent)
		void DeathScreen();

	UFUNCTION(BlueprintImplementableEvent)
		void TutDone();

	UFUNCTION(BlueprintImplementableEvent)
		void GetHit();

private:
	AMyFPSCharacter* MyPlayerCharacter;

	
	
};
