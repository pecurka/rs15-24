// Fill out your copyright notice in the Description page of Project Settings.

#include "Seminarski.h"
#include "RoadSpawner.h"
#include "Put2.h"

// Sets default values
ARoadSpawner::ARoadSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Nadovezivanje = CreateDefaultSubobject<UArrowComponent, UArrowComponent>(TEXT("Nadovezivanje"));
	RootComponent = Nadovezivanje;
	
	/*
	FVector Lokacija = Nadovezivanje->GetComponentLocation();
	FRotator Rotacija = Nadovezivanje->GetComponentRotation();
	for (int i = 0; i < 15; i++)
	{

		Lokacija = Lokacija + FVector(0,i*400,0);
		//GetWorld()->SpawnActor(APut2::StaticClass(), &Lokacija, &Rotacija);
		//GetWorld()->Spa
	}
	*/
}

// Called when the game starts or when spawned
void ARoadSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoadSpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

