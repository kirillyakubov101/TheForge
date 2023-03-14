// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FINALTERMPROJECT_API IDamagable
{
public:
	IDamagable();
	virtual ~IDamagable();

	virtual void DamageActor(float DamageAmount) = 0;
};
