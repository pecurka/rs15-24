// Fill out your copyright notice in the Description page of Project Settings.

#include "Seminarski.h"
#include "Krofna_CPP.h"
#include "Ekran.h"

// Sets default values
AKrofna_CPP::AKrofna_CPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UStaticMeshComponent *Krofna = CreateDefaultSubobject<UStaticMeshComponent,UStaticMeshComponent>(TEXT("krofnica"));
	URotatingMovementComponent *Rotacija = CreateDefaultSubobject<URotatingMovementComponent, URotatingMovementComponent>(TEXT("rotaciona komponenta"));
	UPointLightComponent *Svetlo1 = CreateDefaultSubobject <UPointLightComponent, UPointLightComponent>(TEXT("Svetlo1"));
	UPointLightComponent *Svetlo2 = CreateDefaultSubobject <UPointLightComponent, UPointLightComponent>(TEXT("Svetlo2"));
	USphereComponent *Kolizija = CreateDefaultSubobject <USphereComponent, USphereComponent>(TEXT("Kolizija"));
	Kolizija->SetSphereRadius(65.f);
	Kolizija->Activate(true);
	Kolizija->bGenerateOverlapEvents = true;
	Kolizija->SetRelativeLocation(FVector(0,0,18.f));
	this->RootComponent = Krofna;
	Kolizija->AttachTo(RootComponent);
	Svetlo1->AttachTo(RootComponent);
	Svetlo2->AttachTo(RootComponent);
	Svetlo1->SetRelativeLocation(FVector(0, 0, 65));
	Svetlo2->SetRelativeLocation(FVector(0, 0, -45));
	Svetlo1->SetLightColor(FLinearColor(0.65f, 1.f, 0.875f));
	Svetlo2->SetLightColor(FLinearColor(0.45f, 1.f, 0.82f));
	this->DisableComponentsSimulatePhysics();
	Krofna->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Krofna_SM(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Torus.Shape_Torus'"));
	Krofna->SetStaticMesh(Krofna_SM.Object);


	static ConstructorHelpers::FObjectFinder<UMaterial> Krofna_M(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold'"));
	Krofna->SetMaterial(0, Krofna_M.Object);

	Rotacija->SetActive(true);
	Rotacija->RotationRate = FRotator(120,120,120);

	this->SetActorEnableCollision(true);
	OnActorBeginOverlap.AddDynamic(this, &AKrofna_CPP::OnBeginOverlap);

	
}

// Called when the game starts or when spawned
void AKrofna_CPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKrofna_CPP::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AKrofna_CPP::OnConstruction(const FTransform& Transform)
{
	SetActorScale3D(FVector(0.3,0.3,0.3));
	this->SetLifeSpan(60.f);
}
void AKrofna_CPP::OnBeginOverlap(AActor * Other)
{
	if (Cast<ACharacter, AActor>(Other)  )
	{
		AEkran::NumberOfCoins = AEkran::NumberOfCoins + 1;
		Destroy();
	}
	
}