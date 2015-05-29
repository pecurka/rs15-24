// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RoadSpawner.generated.h"
//#include "Put2.h"
UCLASS()
class SEMINARSKI_API ARoadSpawner : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = "Nadovezivanje", BlueprintReadWrite, EditAnywhere, Meta = (AlowPrivateAccess = "true"))
		UArrowComponent * Nadovezivanje;


public:	
	// Sets default values for this actor's properties
	ARoadSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
