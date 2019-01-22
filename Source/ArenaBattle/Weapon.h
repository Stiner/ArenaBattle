// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class ARENABATTLE_API AWeapon : public AActor
{
	GENERATED_BODY()
    
public:
    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
    class USkeletalMeshComponent* Weapon;
    
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    //UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Stat")
    float BaseDamage;
	
public:
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "WeaponStat")
    float GetDamage() { return BaseDamage; }
};
