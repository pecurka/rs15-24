// Fill out your copyright notice in the Description page of Project Settings.

#include "Seminarski.h"
#include "Put2.h"
#include "RoadSpawner.h"
#include "SkretanjeLevo.h"
#include "SkretanjeDesno.h"
#include "Krofna_CPP.h"
#include "StenaCPP.h"
bool APut2::isEnableSpawnInfinityRoad = true;
int APut2::SpawnPointNumber = 0;
FVector APut2::LokacijaNadovezivanje = FVector(0, 400, 0);
FRotator APut2::RotacijaNadovezivanje = FRotator(0, 0, 0);
FVector APut2::DeltaLocation = FVector(0, 00, 0);
bool APut2::isSpawnSkretanjeLevo = false;
bool APut2::isSpawnSkretanjeDesno = false;
bool APut2::PrviPut = true;
// Sets default values
APut2::APut2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Pod = CreateDefaultSubobject<UStaticMeshComponent, UStaticMeshComponent>(TEXT("Ovo je koren"));
	RootComponent = Pod;
	LeviZid = CreateDefaultSubobject<UStaticMeshComponent, UStaticMeshComponent>(TEXT("koji kurac"));
	DesniZid = CreateDefaultSubobject<UStaticMeshComponent, UStaticMeshComponent>(TEXT("nije nego"));
	Kolizija = CreateDefaultSubobject<UBoxComponent, UBoxComponent>(TEXT(" kolizija"));
	ProstorZaKrofne = CreateDefaultSubobject<UBoxComponent, UBoxComponent>(TEXT("prostor za krofne"));
	Nadovezivanje = CreateDefaultSubobject<UArrowComponent, UArrowComponent>(TEXT("nadovezivanje"));

	Nadovezivanje->AttachTo(RootComponent);
	LeviZid->AttachTo(RootComponent);
	DesniZid->AttachTo(RootComponent);
	Kolizija->AttachTo(RootComponent);
	ProstorZaKrofne->AttachTo(RootComponent);
	//tv->AttachTo(RootComponent);

	//Pod->SetStaticMesh(UStaticMesh())


	static ConstructorHelpers::FObjectFinder<UStaticMesh> PodSM(TEXT("StaticMesh'/Game/StarterContent/Architecture/Floor_400x400.Floor_400x400'"));
	Pod->SetStaticMesh(PodSM.Object);
	static ConstructorHelpers::FObjectFinder<UMaterial> PodM(TEXT("Material'/Game/StarterContent/Materials/M_CobbleStone_Rough.M_CobbleStone_Rough'"));
	Pod->SetMaterial(0, PodM.Object);

	/*Podesi Zid*/
	static ConstructorHelpers::FObjectFinder<UStaticMesh> LeviZid_SM(TEXT("StaticMesh'/Game/StarterContent/Architecture/Wall_400x200.Wall_400x200'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> LeviZid_M(TEXT("Material'/Game/StarterContent/Materials/M_CobbleStone_Rough.M_CobbleStone_Rough'"));
	LeviZid->SetStaticMesh(LeviZid_SM.Object);
	LeviZid->SetMaterial(0, LeviZid_M.Object);
	LeviZid->SetRelativeLocation(FVector(0, 0, 200));
	LeviZid->SetRelativeRotation(FRotator(180, 270, 0));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DesniZid_SM(TEXT("StaticMesh'/Game/StarterContent/Architecture/Wall_400x200.Wall_400x200'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> DesniZid_M(TEXT("Material'/Game/StarterContent/Materials/M_CobbleStone_Rough.M_CobbleStone_Rough'"));
	DesniZid->SetStaticMesh(DesniZid_SM.Object);
	DesniZid->SetMaterial(0, DesniZid_M.Object);
	DesniZid->SetRelativeLocation(FVector(400, 0, 200));
	DesniZid->SetRelativeRotation(FRotator(180, 270, 0));
	Nadovezivanje->SetRelativeLocation(FVector(0, 400, 0));
	Kolizija->SetRelativeLocation(FVector(200, 200, 100));
	Kolizija->SetBoxExtent(FVector(180, 180, 90));
	ProstorZaKrofne->SetRelativeLocation(FVector(200, 360, 20));
	ProstorZaKrofne->SetBoxExtent(FVector(180, 30, 1));
	this->SetActorEnableCollision(true);
	ProstorZaKrofne->bGenerateOverlapEvents = false;
	Pod->bGenerateOverlapEvents = false;
	DesniZid->bGenerateOverlapEvents = false;
	LeviZid->bGenerateOverlapEvents = false;
	Kolizija->bGenerateOverlapEvents = true;
	Kolizija->IsCollisionEnabled();
	this->SetActorEnableCollision(true);

	Nadovezivanje->bGenerateOverlapEvents = false;
	OnActorBeginOverlap.AddDynamic(this, &APut2::OnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &APut2::OnEndOverlap);
	Krofna = nullptr;
	//static ConstructorHelpers::FClassFinder<UBlueprint> kojikurac(TEXT("Blueprint'/Game/Blueprints/Milos1.Milos1'"));
	//FVector vvv=FMath::RandPointInBox(Cast<Box,UBoxComponent>*ProstorZaKrofne);
	//FVector vvv(FMath::RandRange(0, ProstorZaKrofne->GetUnscaledBoxExtent().X), FMath::RandRange(0, ProstorZaKrofne->GetUnscaledBoxExtent().Y)
	//, FMath::RandRange(0, ProstorZaKrofne->GetUnscaledBoxExtent().Z));

	//AActorBaseClass* NewActor = UFunctionLibrary::SpawnBP<AActorBaseClass>(GetWorld(), TheActorBluePrint, SpawnLoc, SpawnRot);
	//UClass *ada = kojikurac.Class.operator UClass *();
	//FRotator RotacijaProstoraZaKrofne = ProstorZaKrofne->GetComponentRotation();
	//FVector vada(3, 3, 3);
	//GetWorld()->SpawnActor(AKrofna_CPP::StaticClass(), &vada, &RotacijaProstoraZaKrofne );

	//LokacijaNadovezivanje =this->Nadovezivanje->GetComponentLocation();
	//RotacijaNadovezivanje =this->Nadovezivanje->GetComponentRotation();
	/*Get world location of first Put2 spawn*/
	if (PrviPut)
	{
		PrviPut = false;
		//LokacijaNadovezivanje = Nadovezivanje->GetComponentLocation()+FVector(0,400,0);
		//RotacijaNadovezivanje = Nadovezivanje->GetComponentRotation();
	}
	static ConstructorHelpers::FObjectFinder<UBlueprint> Vatra(TEXT("Blueprint'/Game/StarterContent/Blueprints/Blueprint_Effect_Fire.Blueprint_Effect_Fire'"));
}

// Called when the game starts or when spawned
void APut2::BeginPlay()
{
	Super::BeginPlay();
	//OnActorBeginOverlap.AddDynamic(this, &APut2::OnOverlap);

}

// Called every frame
void APut2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//this->OnActorBeginOverlap;
}


void APut2::OnBeginOverlap(AActor * Other)
{


	int ChooseNextTurn = FMath::RandRange(0, 5);
	/* if is spawn Turn left, next turn sholud be right or forward */
	if (isSpawnSkretanjeLevo && (ChooseNextTurn == 0))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "If sa skretanjem levo");
		ChooseNextTurn = 1;
		//isSpawnSkretanjeLevo = false;
		//isSpawnSkretanjeDesno = true;
	}
	else if (isSpawnSkretanjeDesno && (ChooseNextTurn == 1))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "IF sa skretanjem desno");
		ChooseNextTurn = 0;
		//isSpawnSkretanjeDesno = false;
		//isSpawnSkretanjeLevo = true;
		//isSpawnSkretanjeDesno = ;
	}


	if (Cast<ACharacter, AActor>(Other) && (ChooseNextTurn >= 2))
	{

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Skretanje Pravo");
		APut2* tmp = Cast<APut2, AActor>(GetWorld()->SpawnActor(APut2::StaticClass(), &LokacijaNadovezivanje, &RotacijaNadovezivanje));

	}

	if (Cast<ACharacter, AActor>(Other) && (ChooseNextTurn == 0))
	{

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Skretanje levo");
		ASkretanjeLevo* tmp = Cast<ASkretanjeLevo, AActor>(GetWorld()->SpawnActor(ASkretanjeLevo::StaticClass(), &LokacijaNadovezivanje, &RotacijaNadovezivanje));
		isSpawnSkretanjeLevo = true;
		isSpawnSkretanjeDesno = false;
	}
	if (Cast<ACharacter, AActor>(Other) && (ChooseNextTurn == 1))
	{

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Skretanje desno");
		ASkretanjeDesno* tmp = Cast<ASkretanjeDesno, AActor>(GetWorld()->SpawnActor(ASkretanjeDesno::StaticClass(), &LokacijaNadovezivanje, &RotacijaNadovezivanje));
		isSpawnSkretanjeDesno = true;

		isSpawnSkretanjeLevo = false;
	}

}

void APut2::OnEndOverlap(AActor * Other)
{
	if (Cast<ACharacter, AActor>(Other))
	{
		GetWorldTimerManager().SetTimer(this, &APut2::HelperDestroy, 10, true);
	}
}
int APut2::sve = 0;
void OnActorBeginOverlap(AActor* Other)
{
	int i = 0;
	while (i < 5)
	{
		i++;
		//GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Blue, "ASDASDAS");
	}
}
void APut2::HelperDestroy()
{
	//Krofna->Destroy();
	this->Destroy();
}
void APut2::OnConstruction(const FTransform& Transforom)
{

	//GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Blue, "Konstrukcija je ok");
	//FVector Lokacija = Nadovezivanje->GetComponentLocation();
	//FRotator Rotacija = this->Nadovezivanje->GetComponentRotation();
	LokacijaNadovezivanje = this->Nadovezivanje->GetComponentLocation();
	RotacijaNadovezivanje = this->Nadovezivanje->GetComponentRotation();
	SpawnPointNumber++;
	if (isEnableSpawnInfinityRoad)
	{
		/*Possibly constructor can get wild*/

		isEnableSpawnInfinityRoad = false;
		for (int i = 0; i < 30; i++)
		{



			GetWorld()->SpawnActor(APut2::StaticClass(), &LokacijaNadovezivanje, &RotacijaNadovezivanje);


		}
	}

	FVector RelativnaLokacijaKrofne(FMath::RandRange(-ProstorZaKrofne->GetUnscaledBoxExtent().X, ProstorZaKrofne->GetUnscaledBoxExtent().X), FMath::RandRange(-ProstorZaKrofne->GetUnscaledBoxExtent().Y, ProstorZaKrofne->GetUnscaledBoxExtent().Y)
		, FMath::RandRange(-ProstorZaKrofne->GetUnscaledBoxExtent().Z, ProstorZaKrofne->GetUnscaledBoxExtent().Z));

	RelativnaLokacijaKrofne = RelativnaLokacijaKrofne + ProstorZaKrofne->GetComponentLocation();
	//AActorBaseClass* NewActor = UFunctionLibrary::SpawnBP<AActorBaseClass>(GetWorld(), TheActorBluePrint, SpawnLoc, SpawnRot);
	//UClass *ada = kojikurac.Class.operator UClass *();
	FRotator RotacijaProstoraZaKrofne = ProstorZaKrofne->GetComponentRotation();
	//FVector vada(3, 3, 3);
	Krofna = Cast<AKrofna_CPP, AActor>(GetWorld()->SpawnActor(AKrofna_CPP::StaticClass(), &RelativnaLokacijaKrofne, &RotacijaProstoraZaKrofne));

	if ((SpawnPointNumber % 10) == 0)
	{
		FVector RelativnaLokacijaStene(FMath::RandRange(-ProstorZaKrofne->GetUnscaledBoxExtent().X, ProstorZaKrofne->GetUnscaledBoxExtent().X), FMath::RandRange(-ProstorZaKrofne->GetUnscaledBoxExtent().Y, ProstorZaKrofne->GetUnscaledBoxExtent().Y)
			, FMath::RandRange(-ProstorZaKrofne->GetUnscaledBoxExtent().Z, ProstorZaKrofne->GetUnscaledBoxExtent().Z));
		RelativnaLokacijaStene += ProstorZaKrofne->GetComponentLocation();
		GetWorld()->SpawnActor(AStenaCPP::StaticClass(), &RelativnaLokacijaStene, &RotacijaProstoraZaKrofne);
	}

}
