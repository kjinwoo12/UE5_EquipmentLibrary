// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentInstance.generated.h"

class UEquipmentAbilitySystemManager;
struct FEquipmentGameplayAbilitySet;
struct FEquipmentGameplayEffectSet;
struct FEquipmentGameplayAttributeSet;

USTRUCT()
struct EQUIPMENTLIBRARY_API FEquipmentActorSpawnOrder
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Equipment)
	TSubclassOf<AActor> EquipmentActorClass;

	UPROPERTY(EditAnywhere, Category = Equipment)
	FName AttachSocket;

	UPROPERTY(EditAnywhere, Category = Equipment)
	FTransform AttachTransform;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class EQUIPMENTLIBRARY_API UEquipmentInstance : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Visual")
	TArray<FEquipmentActorSpawnOrder> SpawningActorOrders;

	UPROPERTY()
	UEquipmentAbilitySystemManager* EquipmentAbilitySystemManager;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TArray<FEquipmentGameplayAbilitySet> GameplayAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TArray<FEquipmentGameplayEffectSet> GameplayEffects;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Attributes")
	TArray<FEquipmentGameplayAttributeSet> GameplayAttributes;

private:
	TArray<TObjectPtr<AActor>> SpawnedEquipmentActors;

public:
	UEquipmentInstance();

	void SpawnEquipmentActorsTo(USkeletalMeshComponent* AttachTargetMesh);
	void DestroyEquipmentActors();

	void GiveAbilitySystemTo(UAbilitySystemComponent* AbilitySystemComponent, UObject* SourceObject);
	void TakeAbilitySystemFrom(UAbilitySystemComponent* AbilitySystemComponent);

	UFUNCTION(BlueprintNativeEvent)
	void OnEquipped();

	UFUNCTION(BlueprintNativeEvent)
	void OnUnequipped();
};
