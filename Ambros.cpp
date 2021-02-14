// Fill out your copyright notice in the Description page of Project Settings.


#include "Ambros.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "Animation/AnimInstance.h"
#include "Engine.h"

// Sets default values
AAmbros::AAmbros()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->InitCapsuleSize(40.f, 94.0f);

	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	AmbrosMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AmbrosMesh"));
	AmbrosMesh->SetupAttachment(GetCapsuleComponent());
	
	/*bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;*/

	/*GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);*/
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(AmbrosMesh);
	FollowCamera->bUsePawnControlRotation = true;
	FollowCamera->SetupAttachment(AmbrosMesh, TEXT("HeadSocket"));

	FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AAmbros::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmbros::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAmbros::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AAmbros::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AAmbros::LookUpAtRate);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AAmbros::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AAmbros::StopCrouch);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAmbros::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAmbros::MoveRight);
}

void AAmbros::MoveForward(float Axis)
{
	if (Axis != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Axis);
	}
}

void AAmbros::MoveRight(float Axis)
{
	if (Axis != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Axis);
	}
}

void AAmbros::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AAmbros::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AAmbros::StartCrouch()
{
	if (!GetCharacterMovement()->IsCrouching())
	{
		GetCharacterMovement()->Crouch();
	}
}

void AAmbros::StopCrouch()
{
	if (GetCharacterMovement()->IsCrouching())
	{
		GetCharacterMovement()->UnCrouch();
	}
}

FRotator AAmbros::GetViewRotation() const
{
	if (Controller)
	{
		return Controller->GetControlRotation();
	}

	return FRotator(RemoteViewPitch / 255.f * 360.f, GetActorRotation().Yaw, 0.f);
}