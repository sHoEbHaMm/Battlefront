// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

	//yawoffset for strafing
	FRotator AimRotation = shooterCharacter->GetBaseAimRotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(shooterCharacter->GetVelocity());
	FRotator deltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
	deltaRotation = FMath::RInterpTo(deltaRotation, deltaRot, deltaTime, 6.f);
	yawOffset = deltaRotation.Yaw;

	charRotationLastFrame = charRotation;
	charRotation = shooterCharacter->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(charRotation, charRotationLastFrame);
	const float Target = Delta.Yaw / deltaTime;
	const float Interp = FMath::FInterpTo(lean, Target, deltaTime, 6.f);
	lean = FMath::Clamp(Interp, -90.f, 90.f);
}