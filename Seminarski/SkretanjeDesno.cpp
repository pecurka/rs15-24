// Fill out your copyright notice in the Description page of Project Settings.

#include "Seminarski.h"
#include "Krofna_CPP.h"
#include "SkretanjeDesno.h"

ASkretanjeDesno::ASkretanjeDesno()
	:APut2()
{
	DesniZid->SetRelativeRotation(FRotator(0, 0, -180));
	DesniZid->SetRelativeLocation(FVector(0, 400, 200));
	Nadovezivanje->SetRelativeLocation(FVector(400,400, 0));
	Nadovezivanje->SetRelativeRotation(FRotator(0, -90, 0));
	//isSpawnSkretanjeDesno = true;
	/*turn left is enable*/
	//isSpawnSkretanjeLevo = false;
}


