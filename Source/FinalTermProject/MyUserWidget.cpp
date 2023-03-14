// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUserWidget.h"
#include "MyFPSCharacter.h"
#include "TutorialComponent.h"


void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MyPlayerCharacter = Cast<AMyFPSCharacter>(GetOwningPlayer()->GetPawn());

	//UE_LOG(LogTemp, Warning, TEXT("MADE"));

	MyPlayerCharacter->OnMoveDelegate.AddUObject(this, &UMyUserWidget::MoveDone); // to the move delegate
	MyPlayerCharacter->OnDashDelegate.AddUObject(this, &UMyUserWidget::DashDone);
	MyPlayerCharacter->OnLookDelegate.AddUObject(this, &UMyUserWidget::LookDone);
	MyPlayerCharacter->OnJumpDelegate.AddUObject(this, &UMyUserWidget::JumpDone);
	MyPlayerCharacter->OnShootDelegate.AddUObject(this, &UMyUserWidget::ShootDone);
	MyPlayerCharacter->OnDeath.AddUObject(this, &UMyUserWidget::DeathScreen);

	MyPlayerCharacter->GetTutorialComponent()->OnTutorialDoneDelegate.AddUObject(this, &UMyUserWidget::TutDone);
	MyPlayerCharacter->OnGetHitDelegate.AddUObject(this, &UMyUserWidget::GetHit);
}

