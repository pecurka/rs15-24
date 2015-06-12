// Fill out your copyright notice in the Description page of Project Settings.

#include "Seminarski.h"
#include "Put2.h"
#include "RoadSpawner.h"
#include "SkretanjeLevo.h"
#include "SkretanjeDesno.h"
#include "Krofna_CPP.h"
#include "StenaCPP.h"

/*Ove var su static jer ih delimo sa SkretanjeDesno i Skretanje Levo*/


/*Da li spanujemo 30 jedinica puta*/
bool APut2::isEnableSpawnInfinityRoad = true;

/*Brojimo broj kreiranih jednica puta*/
int APut2::SpawnPointNumber = 0;
/*Cuvaju Transform sledece jedince puta*/
FVector APut2::LokacijaNadovezivanje = FVector(0, 400, 0);
FRotator APut2::RotacijaNadovezivanje = FRotator(0, 0, 0);
/*Koristi se da spreci skretanje u istu stranu
Posto vucemo 30 jedinca puta, skretanje 2x levo ili 2x desno ce dovesti do preklapanja puta, a to ne zelimo*/
bool APut2::isSpawnSkretanjeLevo = false;
bool APut2::isSpawnSkretanjeDesno = false;
// Sets default values
/*Ima druga verzija konstruktora Klasa(FObjectInitilazier) za koju ima tutorijala po netu, ali posto sam malo glup, i nisam pogledao AActor.cpp lepo, gde jasno pise sve, ovaj konstrukor je uzeo znajacno vreme, 
btw spawn blueprint iz c++ je uspeo*/
APut2::APut2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	/*Kreiranje PodObjekata, oni se drze u nizu ovog Glumca,kad je Glumac unisten i svi njegovi podObjekti su unisteni*/
	/*Generisu Glumcevo ponasanje, tipa oblik, kretanje.....*/
	Pod = CreateDefaultSubobject<UStaticMeshComponent, UStaticMeshComponent>(TEXT("Koren"));
	RootComponent = Pod;
	LeviZid = CreateDefaultSubobject<UStaticMeshComponent, UStaticMeshComponent>(TEXT("LeviZid"));
	DesniZid = CreateDefaultSubobject<UStaticMeshComponent, UStaticMeshComponent>(TEXT("DesniZid"));
	Kolizija = CreateDefaultSubobject<UBoxComponent, UBoxComponent>(TEXT("Kolizija"));
	ProstorZaKrofne = CreateDefaultSubobject<UBoxComponent, UBoxComponent>(TEXT("Prostor za krofne"));
	Nadovezivanje = CreateDefaultSubobject<UArrowComponent, UArrowComponent>(TEXT("Nadovezivanje"));


	/*Pravimo Hijerarhiju*/
	Nadovezivanje->AttachTo(RootComponent);
	LeviZid->AttachTo(RootComponent);
	DesniZid->AttachTo(RootComponent);
	Kolizija->AttachTo(RootComponent);
	ProstorZaKrofne->AttachTo(RootComponent);
	


	/*Konstruktor Helperi za dovlacnej BP, ovde ima malo visaka, posto sam dovlacio isti materijal vise puta, treba lepo razmeti ovaj static, valjda samo jedan put kreirana promenjiva ali joj je doseg samo konstruktor*/
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
		
		ChooseNextTurn = 1;
		
	}
	else if (isSpawnSkretanjeDesno && (ChooseNextTurn == 1))
	{
		
		ChooseNextTurn = 0;
		
	}


	if (Cast<ACharacter, AActor>(Other) && (ChooseNextTurn >= 2))
	{

		
		APut2* tmp = Cast<APut2, AActor>(GetWorld()->SpawnActor(APut2::StaticClass(), &LokacijaNadovezivanje, &RotacijaNadovezivanje));

	}

	if (Cast<ACharacter, AActor>(Other) && (ChooseNextTurn == 0))
	{

		
		ASkretanjeLevo* tmp = Cast<ASkretanjeLevo, AActor>(GetWorld()->SpawnActor(ASkretanjeLevo::StaticClass(), &LokacijaNadovezivanje, &RotacijaNadovezivanje));
		isSpawnSkretanjeLevo = true;
		isSpawnSkretanjeDesno = false;
	}
	if (Cast<ACharacter, AActor>(Other) && (ChooseNextTurn == 1))
	{

		
		ASkretanjeDesno* tmp = Cast<ASkretanjeDesno, AActor>(GetWorld()->SpawnActor(ASkretanjeDesno::StaticClass(), &LokacijaNadovezivanje, &RotacijaNadovezivanje));
		isSpawnSkretanjeDesno = true;

		isSpawnSkretanjeLevo = false;
	}

}

void APut2::OnEndOverlap(AActor * Other)
{
	if (Cast<ACharacter, AActor>(Other))
	{
		/*Ovaj metod je banovan iz sledecih izdanja ali je najlaksi*/
		/*Vezemo tajmer za nas objekat, metod koji se poziva mora imati odredjeni potpis pa otuda i naziv HelperDestroy */
		GetWorldTimerManager().SetTimer(this, &APut2::HelperDestroy, 10, true);
	}
}


void APut2::HelperDestroy()
{
	
	this->Destroy();
}
void APut2::OnConstruction(const FTransform& Transforom)
{
	/**********************************
	Stvori 30 puteva kad igra pocne
	********************************/

	/*Update parametre stvranja sledece jedinice puta*/
	LokacijaNadovezivanje = this->Nadovezivanje->GetComponentLocation();
	RotacijaNadovezivanje = this->Nadovezivanje->GetComponentRotation();
	SpawnPointNumber++;
	if (isEnableSpawnInfinityRoad)
	{
		/*Possibly the constructor can get wild*/
		/*Ovde se dogadja rekurzija, ne direktna ali "indirektna", OnConstruction se poziva kad se Glumac stvori*/
		isEnableSpawnInfinityRoad = false;
		for (int i = 0; i < 30; i++)
		{

			GetWorld()->SpawnActor(APut2::StaticClass(), &LokacijaNadovezivanje, &RotacijaNadovezivanje);

		}
	}



	/*Stvaranje krovne na random poziciju*/
	FVector RelativnaLokacijaKrofne(FMath::RandRange(-ProstorZaKrofne->GetUnscaledBoxExtent().X, ProstorZaKrofne->GetUnscaledBoxExtent().X), FMath::RandRange(-ProstorZaKrofne->GetUnscaledBoxExtent().Y, ProstorZaKrofne->GetUnscaledBoxExtent().Y)
		, FMath::RandRange(-ProstorZaKrofne->GetUnscaledBoxExtent().Z, ProstorZaKrofne->GetUnscaledBoxExtent().Z));

	RelativnaLokacijaKrofne = RelativnaLokacijaKrofne + ProstorZaKrofne->GetComponentLocation();
	
	FRotator RotacijaProstoraZaKrofne = ProstorZaKrofne->GetComponentRotation();
	
	Krofna = Cast<AKrofna_CPP, AActor>(GetWorld()->SpawnActor(AKrofna_CPP::StaticClass(), &RelativnaLokacijaKrofne, &RotacijaProstoraZaKrofne));


	/*Stvramo Stenu svakih 10 jedinica puta*/
	if ((SpawnPointNumber % 10) == 0)
	{
		FVector RelativnaLokacijaStene(FMath::RandRange(-ProstorZaKrofne->GetUnscaledBoxExtent().X, ProstorZaKrofne->GetUnscaledBoxExtent().X), FMath::RandRange(-ProstorZaKrofne->GetUnscaledBoxExtent().Y, ProstorZaKrofne->GetUnscaledBoxExtent().Y)
			, FMath::RandRange(-ProstorZaKrofne->GetUnscaledBoxExtent().Z, ProstorZaKrofne->GetUnscaledBoxExtent().Z));
		RelativnaLokacijaStene += ProstorZaKrofne->GetComponentLocation();
		GetWorld()->SpawnActor(AStenaCPP::StaticClass(), &RelativnaLokacijaStene, &RotacijaProstoraZaKrofne);
	}

}
/*Ova funcnkija je pozivna iz BP, koristi se da restartujemo igru*/
void APut2::Restart()
{
	APut2::isEnableSpawnInfinityRoad = true;
	APut2::LokacijaNadovezivanje = FVector(0, 0, 0);
	APut2::RotacijaNadovezivanje = FRotator(0, 0, 0);
	APut2::isSpawnSkretanjeLevo = false;
	APut2::isSpawnSkretanjeDesno = false;
	APut2::PrviPut = true;
	AEkran::NumberOfCoins = 0;
}