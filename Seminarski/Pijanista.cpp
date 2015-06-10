// Fill out your copyright notice in the Description page of Project Settings.

#include "Seminarski.h"
#include "Pijanista.h"
#include "Put2.h"
#include "SkretanjeLevo.h"
#include "SkretanjeDesno.h"
// Sets default values
APijanista::APijanista()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USpringArmComponent *CameraBoom = CreateDefaultSubobject<USpringArmComponent, USpringArmComponent>(TEXT("CameraBoom"));
	//RootComponent = Mesh;
	/*Kreiramo komponente, MovementCopmponet,SkelatalMesh,ColisionCilindar su vec bili kreirani....*/
	RootComponent = CapsuleComponent;
	CameraBoom->AttachTo(RootComponent);
	FollowCamera = CreateDefaultSubobject<UCameraComponent, UCameraComponent>(TEXT("FollowCamera"));
	Mesh->AttachTo(RootComponent);
	FollowCamera->AttachTo(CameraBoom);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Mesh_SM(TEXT("SkeletalMesh'/Game/ThirdPersonBP/Character/ThirdPersonSkelMesh.ThirdPersonSkelMesh'"));
	Mesh->SetSkeletalMesh(Mesh_SM.Object);
	RootComponent->Activate(true);
	RootComponent->SetMobility(EComponentMobility::Movable);
	
	this->InputEnabled();
	this->AnimUpdateRateFrameCount = 10;
	this->AnimUpdateRateShiftTag = 10;
	ConstructorHelpers::FObjectFinder<UAnimationAsset> bb(TEXT("AnimSequence'/Game/ThirdPersonBP/Character/NijeNego.NijeNego'"));
	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	/*Koristili smo njihovu animaciju, intuitvno je jasno kako cela stvar radi, MovementCompoent da postvalja odgovarajuca polja animciji, animacija ce to da registruje i da menja svoje stanje*/
	Mesh->SetAnimation(bb.Object);
	
	Mesh->Activate(true);

	/*Vezujemo funkcionalnost za OnActorBeginOverlap, vezani metod mora imati odredjeni potpis */
	OnActorBeginOverlap.AddDynamic(this, &APijanista::OnBeginOverlap);
	Cam = CameraBoom;





	/*Stvari koji se imenom ocigledne nece biti komentarisane*/
	this->SetActorRelativeScale3D(FVector(0.4, 0.4, 0.4));

}

// Called when the game starts or when spawned
void APijanista::BeginPlay()
{
	Super::BeginPlay();
	
	APijanista::SpringArmLeft = false;
	APijanista::SpringArmRight = false;
	APijanista::RightVector = GetActorRightVector();

	APijanista::ForwardVector = GetActorForwardVector();

	this->SetActorLocation(FVector(400, -200, 0));

}

// Called every frame
void APijanista::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
/*Vezujemo metode za specificno ime, a specificno ime smo vezali za specificnu dugmad i to je uradjeno u editoru i deo je PlayerController klase,
koja je dinamicki programirana u editoru, mogla je biti uradjena i u c++ ali onako je bilo najlakse, i stvarno ne treba izmisljati toplu vodu po svaku cenu,
bilo je tesko shvatiti sta se tu tacno dogadja. Samo klik,klik, mouse input, touch input, keyboard input i sve je vec Epic uradio za nas*/
void APijanista::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	/*Ovi metodi moraju imati odredjeni potpis, pozivaju se svaki Frame*/
	InputComponent->BindAxis("MoveForward", this, &APijanista::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APijanista::MoveRight);
	InputComponent->BindAction("Jump", IE_Pressed, this, &APijanista::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &APijanista::OnStopJump);

}

void APijanista::MoveForward(float Value)
{

	AddMovementInput(APijanista::ForwardVector, 5);

}
/*Koristimo za skretanje desno i levo*/
/*Ovo je malo divlje uradjeno, SkelatalComponent ima forward vector i right vector koji se uglavnom koriste da se odredi smer kretanja,nisam to provise istrazivo,
samo znam da se rotacijom Skeleta nece rotirati i pomenti vectori, tako da je to bilo potrebno rucno uraditi
Kad je Trkac(Pijanista) na skretanju, sto oslusnemo metodom OnBeginOverlap, postavimo SpringArmLeft i SpringArmRight(imena mozda nisu najsrecnija) na true,
i ako igrac pritsne skretanje u pravom smeru, V>0 je pravi smer, onda rotiramo kameru, rotiramo Skelet i vectore u pravom smeru
I ni to nije najsrecnije jer se naglo dogodi, trebalo je to postepeno uraditi, za po npr 10',umesati neki tajmer....*/
void APijanista::MoveRight(float V)
{
	if (V != 0)
	{

		if (!APijanista::SpringArmLeft && !APijanista::SpringArmRight)
		{
			
			AddMovementInput(RightVector, V * 4);
		}
		else if (APijanista::SpringArmLeft && V>0)
		{
			
			Mesh->SetWorldRotation(Mesh->GetComponentRotation() + FRotator(0, 90, 0));
			Cam->SetWorldRotation(Cam->GetComponentRotation() + FRotator(0, 90, 0));
			APijanista::SpringArmLeft = false;
		
			ForwardVector = ForwardVector.RotateAngleAxis(90, FVector(0, 0, 1));
			RightVector = RightVector.RotateAngleAxis(90, FVector(0, 0, 1));
			
		}
		else if (APijanista::SpringArmRight && V<0)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "else if (APijanista::SpringArmRight");
			Mesh->SetWorldRotation(Mesh->GetComponentRotation() + FRotator(0, -90, 0));
			Cam->SetWorldRotation(Cam->GetComponentRotation() + FRotator(0, -90, 0));
			APijanista::SpringArmRight = false;
			
			ForwardVector = ForwardVector.RotateAngleAxis(-90, FVector(0, 0, 1));
			RightVector = RightVector.RotateAngleAxis(-90, FVector(0, 0, 1));
			
		}
	}
	
}
/*MovementComponent ce sve uraditi za nas, naravno inutivno je jasno kako bi sami skocili*/
void APijanista::OnStartJump()
{

	Jump();
}
void APijanista::OnStopJump()
{

}

/*Metod kojim oslusukjemo da li smo na skretanju*/
void APijanista::OnBeginOverlap(AActor *Other)
{


	if (Cast<ASkretanjeLevo, AActor>(Other))
	{

		APijanista::SpringArmLeft = true;
	}
	else
		if (Cast<ASkretanjeDesno, AActor>(Other))
		{
	
			APijanista::SpringArmRight = true;
			
		}
	
}