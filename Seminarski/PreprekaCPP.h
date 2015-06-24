// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PreprekaCPP.generated.h"

UCLASS()
class SEMINARSKI_API APreprekaCPP : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APreprekaCPP();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/*Bice editable u editoru i takodje sve ostalo sto pise,SimpleDisplay znaci da ce nam ga editor otvoriti u obliku tacno kakav nam treba*/
	UPROPERTY(Category = "Izgled", BlueprintReadWrite, EditAnywhere, SimpleDisplay,
		Meta = (AlowPrivateAccess = "true"))
		UStaticMeshComponent* Koren;

	/*parametri animacije*/
private:
	float Parametar;
	float Delta;

};
