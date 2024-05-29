// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "Battlefront/Weapons/Weapon.h"
#include "Battlefront/Character/ShooterCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UCombatComponent::SetAiming(bool bSetAimTo)
{
	bIsAiming = bSetAimTo;
	ServerSetAiming(bSetAimTo);
}

void UCombatComponent::ServerSetAiming_Implementation(bool bSetAimTo)
{
	bIsAiming = bSetAimTo;
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCombatComponent, equippedWeapon);
	DOREPLIFETIME(UCombatComponent, bIsAiming);
}

void UCombatComponent::EquipWeapon(AWeapon* weaponToEquip)
{
	if (shooterCharacter == NULL || weaponToEquip == NULL)
		return;

	equippedWeapon = weaponToEquip;
	equippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);
	const USkeletalMeshSocket* handSocket =  shooterCharacter->GetMesh()->GetSocketByName(FName("RightHandSocket"));

	if (handSocket)
	{
		handSocket->AttachActor(equippedWeapon, shooterCharacter->GetMesh());
	}

	equippedWeapon->SetOwner(shooterCharacter);
}

