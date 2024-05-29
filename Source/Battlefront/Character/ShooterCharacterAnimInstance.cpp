// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UShooterCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	shooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
}

void UShooterCharacterAnimInstance::NativeUpdateAnimation(float deltaTime)
{
	Super::NativeUpdateAnimation(deltaTime);

	if (shooterCharacter == nullptr)
	{
		shooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	}

	if (shooterCharacter == nullptr) return;

	FVector velocity = shooterCharacter->GetVelocity();
	velocity.Z = 0.f;
	Speed = velocity.Size();

	bIsInAir = shooterCharacter->GetCharacterMovement()->IsFalling();

	bIsAccelerating = shooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;

	bWeaponEquipped = shooterCharacter->isWeaponEquipped();

	bIsCrouched = shooterCharacter->bIsCrouched;

	bAiming = shooterCharacter->isAiming();
}