// Fill out your copyright notice in the Description page of Project Settings.

#include "Seminarski.h"
#include "PreprekaCPP.h"


// Sets default values
APreprekaCPP::APreprekaCPP()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	/*Kreiramo jedan podobjekat, postavimo ga za koren, ostalo podobjektte kreiramo u editoru, jer tako treba,
	naravno logiku cemo zadati ovde u Tick fun. koja se poziva svaki frame*/
	Koren = CreateDefaultSubobject<UStaticMeshComponent, UStaticMeshComponent>(TEXT("Koren"));
	RootComponent = Koren;
	/*Parametar animacija*/
	Parametar = 0;
	/*Prirastaj animcacije*/
	Delta = 0.05;
	SetActorRelativeScale3D(FVector(0.4, 0.4, 0.4));
}

// Called when the game starts or when spawned
void APreprekaCPP::BeginPlay()
{
	Super::BeginPlay();

	/*Stavimo duzinu zivota ovde jer nam se editor rusi ako ga stavimo u konstrukotr*/
	SetLifeSpan(20.f);

}

// Called every frame
void APreprekaCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	/*Neka funkcija*/
	Parametar += Delta;
	float Y = 3 * FMath::Cos(Parametar);
	float X = 3 * Parametar;
	float Z = 3 * FMath::Sin(Parametar) + Parametar;
	SetActorRelativeLocation(GetActorLocation() + FVector(X, Y, Z) * FMath::Sign(Delta));
	/*+0.05 se lepo zaokrugli na ovom kompu, mozda treba dodati dodati neku gresku*/
	/*Kada smo sigli do 2*PI i 0 idemo nazad istim  putem*/
	if (Parametar >= 2 * PI || Parametar <= 0)
		Delta = -Delta;



}

