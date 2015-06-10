// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Pijanista.generated.h"

UCLASS()
class SEMINARSKI_API APijanista : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	APijanista();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	//Kameru su izlozili blueprintu i kasnije cemo je vizualno podesiti kako nam bude odgovarlo, malo iznad glumca
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UCameraComponent *FollowCamera;


	UFUNCTION()
		virtual void Move();
	UFUNCTION()
		virtual void MoveForward(float Value);
	UFUNCTION()
		virtual void MoveRight(float Value);
	UFUNCTION()
		virtual void OnStartJump();
	UFUNCTION()
		virtual void OnStopJump();
	UFUNCTION()
		virtual void OnBeginOverlap(AActor * Other);
	USpringArmComponent *Cam;



	//Koristi se da odredi da li smo na skretanju
	bool SpringArmLeft;
	bool SpringArmRight;
	/*Smer kretanja Pijaniste*/
	FVector RightVector;
	FVector ForwardVector;
};
