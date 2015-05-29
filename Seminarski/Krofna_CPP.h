// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Krofna_CPP.generated.h"

UCLASS()
class SEMINARSKI_API AKrofna_CPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKrofna_CPP();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	void OnConstruction(const FTransform& Transforom) override;
	UFUNCTION()
	void OnBeginOverlap(AActor * Other);
};
