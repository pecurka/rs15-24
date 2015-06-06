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


	//DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCharacterMovementUpdatedSignature, float, DeltaSeconds, FVector, OldLocation, FVector, OldVelocity);
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UCameraComponent *FollowCamera;


	UFUNCTION()
		virtual void Move();
	UFUNCTION()
		virtual void MoveForward(float Value);
	UFUNCTION()
		virtual void MoveRight(float Value);
	UFUNCTION()
		virtual void Jump1(float value);
	UFUNCTION()
		virtual void OnStartJump();
	UFUNCTION()
		virtual void OnStopJump();
	UFUNCTION()
		virtual void OnBeginOverlap(AActor * Other);
	USpringArmComponent *Cam;

	/*Ovo nije meta-programiranje ali ce to mozda postati*/
	/**************************************************
	***************************************************
	***************************************************/
	//Ovo ce biti banovano iz sledecih izdanja, izgleda gadno kao Slajd
	UAnimMontage* ttt;

	//Hhahah malo loseg programiranja,steta sto nemamo podrsku za B prolog ili ne bi morali da radimo rekurziju
	bool SpringArmLeft;
	bool SpringArmRight;
	/*E ovo je kul*/
	FVector RightVector;
	FVector ForwardVector;
};
