// Fill out your copyright notice in the Description page of Project Settings.

#include "Seminarski.h"
#include "Vatra.h"


// Sets default values
AVatra::AVatra()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UParticleSystemComponent * Koren = CreateDefaultSubobject<UParticleSystemComponent, UParticleSystemComponent>("FC Barselona");
	RootComponent = Koren;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Vatra_Particles(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	Koren->SetTemplate(Vatra_Particles.Object);
}

// Called when the game starts or when spawned
void AVatra::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AVatra::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
