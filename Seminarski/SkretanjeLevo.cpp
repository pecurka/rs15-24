// Fill out your copyright notice in the Description page of Project Settings.

#include "Seminarski.h"
#include "SkretanjeLevo.h"
#include "Krofna_CPP.h"
#include "Put2.h"

ASkretanjeLevo::ASkretanjeLevo()
	:APut2()
{
	LeviZid->SetRelativeRotation(FRotator(0,0,-180));
	LeviZid->SetRelativeLocation(FVector(0, 400, 200));
	Nadovezivanje->SetRelativeLocation(FVector(0,0,0));
	Nadovezivanje->SetRelativeRotation(FRotator(0,90,0));
	//isSpawnSkretanjeLevo = true;
	//isSpawnSkretanjeDesno = false;
}
/*
void ASkretanjeLevo::OnConstruction(const FTransform & Transform)
{
	
	
}
*/

