// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "StenaCPP.generated.h"

UCLASS()
class SEMINARSKI_API AStenaCPP : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStenaCPP();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;


	UFUNCTION()
		void OnBeginOverlap(AActor * Other);
};
