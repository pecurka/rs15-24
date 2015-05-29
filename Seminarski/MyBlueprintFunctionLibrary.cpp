// Fill out your copyright notice in the Description page of Project Settings.

#include "Seminarski.h"
#include "MyBlueprintFunctionLibrary.h"
//#include "Engine.h"


/*
UMyBlueprintFunctionLibrary::UMyBlueprintFunctionLibrary(const class FObjectInitializer& PCIP)
 : Super(PCIP)
{

	//UBlueprintFunctionLibrary(PCIP);
	
}
*/
static int brojCoins=0;
int UMyBlueprintFunctionLibrary::getBrojCoins(void)
 {
	 
	 return brojCoins;
 }

void UMyBlueprintFunctionLibrary::setBrojCoins(int Value)
{
	brojCoins = Value;
}

void UMyBlueprintFunctionLibrary::addOne()
{

	brojCoins = brojCoins + 1;

}