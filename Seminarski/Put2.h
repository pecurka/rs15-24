// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Krofna_CPP.h"
#include "Put2.generated.h"
#include "PreprekaCPP.h"


UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class SEMINARSKI_API APut2 : public AActor

{
	GENERATED_BODY()

public:
	static bool isEnableSpawnInfinityRoad;
	/**/
	static int SpawnPointNumber;
	/*Delimo transform sa svim klasama*/
	static FVector LokacijaNadovezivanje;
	static FRotator RotacijaNadovezivanje;
	/*Onemogucavamo duplo skretanje u istu straanu*/
	static bool isSpawnSkretanjeLevo;
	static bool isSpawnSkretanjeDesno;
	static FVector DeltaLocation;

	/*Ovako izlazemo nase Komponente BP, Ovu klasu je kompletno uradjena u C++, ali kad bi iz nje izveli BP, onda bi mogli vizualno da editujemo svojstva
	a logika bi nam ostala u C++*/
	/*Kategorija sluzi BP, prilicno je ocigledno onom ko zna nesto iz BP*/
	UPROPERTY(Category = "StaticMeshCom", BlueprintReadWrite, EditAnywhere, Meta = (AlowPrivateAccess = "true"))
		UStaticMeshComponent* Pod;



	UPROPERTY(Category = "StaticMeshCom", BlueprintReadWrite, EditAnywhere, SimpleDisplay,
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

	UPROPERTY(Category = "Nesto", BlueprintReadWrite, EditAnywhere, SimpleDisplay,
		Meta = (AlowPrivateAccess = "true"))
		UBlueprint * Vatra;


	APut2();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	//Called when constructior finsih
	virtual void OnConstruction(const FTransform &Transform) override;

	/*Ove metode nisu morale da budu virutalne*/
	UFUNCTION()
		virtual void OnBeginOverlap(AActor* OtherActor);
	UFUNCTION()
		virtual void OnEndOverlap(AActor* OtherActor);
	virtual void HelperDestroy();
	

	/*Use to restart static vars in the APut2 */
	UFUNCTION(BlueprintCallable, Category = "APut2")
		static void Restart();

private:
	/*Ovo nam sluzi za smestimo dovuceni BP, koji je izvedena klasa PreprekaCPP, sto tacno i pise u deklaraciju*/
	TSubclassOf<APreprekaCPP> Prepreka;
};
