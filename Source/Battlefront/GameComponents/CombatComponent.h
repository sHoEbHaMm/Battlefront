// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class AWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLEFRONT_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	friend class AShooterCharacter;

	void EquipWeapon(AWeapon* weaponToEquip);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void SetAiming(bool bSetAimTo);
	
	UFUNCTION(Server, Reliable)
	void ServerSetAiming(bool bSetAimTo);

	UFUNCTION()
	void OnRep_EquippedWeapon();

private:
	class AShooterCharacter* shooterCharacter;

	UPROPERTY(ReplicatedUsing = OnRep_EquippedWeapon)
	class AWeapon* equippedWeapon;

	UPROPERTY(Replicated)
	bool bIsAiming;
public:	

	
		
};
