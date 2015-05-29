// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"
/**
 * target is Kismet math libary, e to bi bilo kul ali u stvari nije :-) 
 */
UCLASS()
class SEMINARSKI_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/*	UPROPERTY(BlueprintReadWrite,Category = "MyBlueprintFunctionLibrary")
		static int brojCoins;
	*/
	    UFUNCTION(BlueprintCallable, Category = "MyBlueprintFunctionLibrary")
		static void setBrojCoins(int32 Value);
      
		UFUNCTION(BlueprintCallable, Category = "MyBlueprintFunctionLibrary")
	    static int32 getBrojCoins();

		UFUNCTION(BlueprintCallable, Category = "MyBlueprintFunctionLibrary")
	    static void addOne();

};
