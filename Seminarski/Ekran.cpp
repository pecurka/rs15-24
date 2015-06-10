// Fill out your copyright notice in the Description page of Project Settings.

#include "Seminarski.h"
#include "Ekran.h"


/*GameMode ce instanirati HUD kada igra pocne, zato ovo mora da bude static*/
int AEkran::NumberOfCoins = 0;
void AEkran::DrawHUD(void)
{
	

	UFont *font=AHUD::GetFontFromSizeIndex(10);

	FString tekst = "Sakupljeno:  ";
	tekst = tekst + FString::FromInt(NumberOfCoins);
	
	
	DrawText(tekst, FLinearColor::Red,20, 0, font, 5, true);
}