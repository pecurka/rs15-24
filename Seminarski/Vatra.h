// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Vatra.generated.h"

UCLASS()
class SEMINARSKI_API AVatra : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVatra();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;



};
