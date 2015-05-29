// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Krofna_CPP.h"
#include "Put2.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterBeginOverlapSignature, class ACharacter*, OtherActor);

UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class SEMINARSKI_API APut2 : public AActor

{
	GENERATED_BODY()
	
public:
	static int sve;
	static bool isEnableSpawnInfinityRoad;
	/*Join the party   -:)*/
	static int SpawnPointNumber;
	/*Lokacija nadovezivanja, verovatno moramo ovako zbog skretanja*/
	static FVector LokacijaNadovezivanje;
	static FRotator RotacijaNadovezivanje;
	static bool PrviPut;
	static bool isSpawnSkretanjeLevo;
	static bool isSpawnSkretanjeDesno;
	static FVector DeltaLocation;
	AKrofna_CPP *Krofna;
	UPROPERTY(Category = "StaticMeshCom", BlueprintReadWrite, EditAnywhere, Meta = (AlowPrivateAccess="true"))
		UStaticMeshComponent* Pod;
		
	

	UPROPERTY(Category = "StaticMeshCom", BlueprintReadWrite, EditAnywhere, SimpleDisplay ,
		Meta = (AlowPrivateAccess = "true"))
		UStaticMeshComponent* LeviZid;
	
	UPROPERTY(Category = "StaticMeshCom", BlueprintReadWrite, EditAnywhere, SimpleDisplay,
		Meta = (AlowPrivateAccess = "true"))
		UStaticMeshComponent* DesniZid;


	
	UPROPERTY(Category = "Kolizija", BlueprintReadWrite, EditAnywhere, SimpleDisplay,
		Meta = (AlowPrivateAccess = "true"))
		UBoxComponent * Kolizija;
	
	UPROPERTY(Category = "Kolizija", BlueprintReadWrite, EditAnywhere, SimpleDisplay,
		Meta = (AlowPrivateAccess = "true"))
		UBoxComponent * ProstorZaKrofne;
	
	UPROPERTY(Category = "Nad", BlueprintReadWrite, EditAnywhere, SimpleDisplay,
		Meta = (AlowPrivateAccess = "true"))
		UArrowComponent * Nadovezivanje;
	UPROPERTY(Category = "Bool", BlueprintReadWrite, EditAnywhere, SimpleDisplay,
		Meta = (AlowPrivateAccess = "true"))
		bool OmogucenoSkretanjeLevo;

	//UFUNCTION(BlueprintCallable, Category = "Funkcija")
		//FString odrediSledeceSkretanje();
	// Sets default values for this actor's properties
	
	APut2();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Called when constructior finsih
	virtual void OnConstruction(const FTransform &Transform) override;

	//FActorBeginOverlapSignature OnActorBeginOverlap;
	UFUNCTION()
	virtual void OnBeginOverlap(AActor* OtherActor);
	UFUNCTION()
	virtual void OnEndOverlap(AActor* OtherActor);
	virtual void HelperDestroy();
	//UFUNCTION()
	//void OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	
	//FCharacterBeginOverlapSignature Zovi();
};
