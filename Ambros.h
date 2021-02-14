// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Ambros.generated.h"

class UInputComponet;


UCLASS()
class LESSPOWER_API AAmbros : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAmbros();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
		class USkeletalMeshComponent* AmbrosMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	void MoveForward(float Axis);
	void MoveRight(float Axis);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void StartCrouch();
	void StopCrouch();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	FRotator GetViewRotation() const override;
	
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
