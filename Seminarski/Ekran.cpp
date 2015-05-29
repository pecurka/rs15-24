// Fill out your copyright notice in the Description page of Project Settings.

#include "Seminarski.h"
#include "Ekran.h"


int AEkran::NumberOfCoins = 0;
void AEkran::DrawHUD(void)
{
	
	//AHUD::DrawText(const FString& Text, FVector2D Position, UFont* TextFont, FVector2D FontScale, FColor TextColor)
	//FObjectInitializer aaa();
	UFont *font=AHUD::GetFontFromSizeIndex(10);

	FString tekst = "Sakupljeno:  ";
	tekst = tekst + FString::FromInt(NumberOfCoins);
	//DrawText(TEXT("Sakupljeno"),FLinearColor::Red,0,0,font,1,true);
	
	DrawText(tekst, FLinearColor::Red,20, 0, font, 5, true);
}