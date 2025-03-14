// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"

// Sets default values
APlayerChar::APlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Initial camera component setup.
	PlayerCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Cam"));

	// Attach camera to character mesh and head bone.
	PlayerCamComp->SetupAttachment(GetMesh(), "head");

	// Share cmaera rotation with controller.
	PlayerCamComp->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Calls function to move forward and backward.
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerChar::MoveForward);
	
	// Calls function to move left and right.
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerChar::MoveRight);
	
	// Calls function to look up and down.
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerChar::AddControllerPitchInput);
	
	// Calls function to turn left and right.
	PlayerInputComponent->BindAxis("Turn", this, &APlayerChar::AddControllerYawInput);
	
	// Calls function to start jump movement.
	PlayerInputComponent->BindAction("JumpEvent", IE_Pressed, this, &APlayerChar::StartJump);
	
	// Calls function to stop jump movement.
	PlayerInputComponent->BindAction("JumpEvent", IE_Released, this, &APlayerChar::StopJump);

	// Calls function for character to interact with objects.
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerChar::FindObject);
}

void APlayerChar::MoveForward(float axisValue)
{
	// Defines forward and backward movement along the x-axis.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, axisValue);
}

void APlayerChar::MoveRight(float axisValue)
{
	// Defines right and left movement along the y-axis.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, axisValue);
}

void APlayerChar::StartJump()
{
	// Defines jump action to begin when button is pressed.
	bPressedJump = true;
}

void APlayerChar::StopJump()
{
	// Defines jump action to end when button is released.
	bPressedJump = false;
}

void APlayerChar::FindObject()
{
}

