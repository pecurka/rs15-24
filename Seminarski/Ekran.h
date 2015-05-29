// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "Ekran.generated.h"

/**
 * 
 */
UCLASS()
class SEMINARSKI_API AEkran : public AHUD
{
	GENERATED_BODY()

	virtual void DrawHUD() override;
public:
	static int NumberOfCoins;
};
