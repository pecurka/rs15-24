// Fill out your copyright notice in the Description page of Project Settings.

#include "Seminarski.h"
#include "StenaCPP.h"


// Sets default values
AStenaCPP::AStenaCPP()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UStaticMeshComponent* Oblik = CreateDefaultSubobject<UStaticMeshComponent, UStaticMeshComponent>(TEXT("izvedeni blueprint ce ovo registovati kao svoje ime a mozda jos i nesto"));
	UCapsuleComponent *Kolizija = CreateDefaultSubobject<UCapsuleComponent, UCapsuleComponent>(TEXT("Kolizija"));
	UParticleSystemComponent * Vatra = CreateDefaultSubobject<UParticleSystemComponent, UParticleSystemComponent>("Vatra");
	//UParticleSystemComponent * Eksplozija = CreateDefaultSubobject<UParticleSystemComponent, UParticleSystemComponent>("Ekspozija");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Oblik_SM(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Rock.SM_Rock'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> Oblik_M(TEXT("Material'/Game/StarterContent/Materials/M_CobbleStone_Rough.M_CobbleStone_Rough'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Vatra_Particles(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));

	Oblik->SetStaticMesh(Oblik_SM.Object);
	Oblik->SetMaterial(0, Oblik_M.Object);
	Kolizija->SetCapsuleRadius(100.f);
	Kolizija->SetCapsuleHalfHeight(200.f);
	Kolizija->SetRelativeLocation(FVector(0, 0, 92));
	Vatra->SetTemplate(Vatra_Particles.Object);
	Vatra->SecondsBeforeInactive = 0;
	Vatra->CustomTimeDilation = 1;
	Vatra->SetRelativeLocation(FVector(30, 0, 215));
	Kolizija->bGenerateOverlapEvents = true;

	RootComponent = Oblik;
	Kolizija->AttachTo(RootComponent);
	Vatra->AttachTo(RootComponent);
	SetActorRelativeScale3D(FVector(0.3, 0.3, 0.3));

	OnActorBeginOverlap.AddDynamic(this, &AStenaCPP::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AStenaCPP::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AStenaCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetLifeSpan(30.f);

}

void AStenaCPP::OnBeginOverlap(AActor * Other)
{
	if (Cast<ACharacter, AActor>(Other))
	{
		Other->Destroy();
	}
	/*Ovo ce se mozda promeniti ako dodamo ekspolizju,tj. mozda budemo asset koji ce Runnera da napravi neunistivim*/

}