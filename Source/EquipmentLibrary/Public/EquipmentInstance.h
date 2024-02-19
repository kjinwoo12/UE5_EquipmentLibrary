// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentGameplayAbilitySet.h"
#include "EquipmentGameplayEffectSet.h"
#include "EquipmentGameplayAttributeSet.h"
#include "EquipmentInstance.generated.h"

EQUIPMENTLIBRARY_API DECLARE_LOG_CATEGORY_EXTERN(LogEquipmentInstance, Log, All);

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

private:
	TArray<TObjectPtr<AActor>> SpawnedEquipmentActors;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TArray<FEquipmentGameplayAbilitySet> GameplayAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TArray<FEquipmentGameplayEffectSet> GameplayEffects;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Attributes")
	TArray<FEquipmentGameplayAttributeSet> GameplayAttributes;

private:
	TArray<FGameplayAbilitySpecHandle> GameplayAbilitySpecHandles;
	TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;
	TArray<TObjectPtr<UAttributeSet>> GameplayAttributeInstances;

public:
	void SpawnEquipmentActorsTo(USkeletalMeshComponent* AttachTargetMesh);

	void DestroyEquipmentActors();

	void GiveAbilitySystemTo(UAbilitySystemComponent* AbilitySystemComponent, UObject* SourceObject);
	void TakeAbilitySystemFrom(UAbilitySystemComponent* AbilitySystemComponent);

private:
	void GiveAbilityTo(UAbilitySystemComponent* AbilitySystemComponent, UObject* SourceObject);
	void TakeAbilityFrom(UAbilitySystemComponent* AbilitySystemComponent);

	void GiveEffectTo(UAbilitySystemComponent* AbilitySystemComponent, UObject* SourceObject);
	void TakeEffectFrom(UAbilitySystemComponent* AbilitySystemComponent);

	void GiveAttributeTo(UAbilitySystemComponent* AbilitySystemComponent, UObject* SourceObject);
	void TakeAttributeFrom(UAbilitySystemComponent* AbilitySystemComponent);

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnEquipped();

	UFUNCTION(BlueprintNativeEvent)
	void OnUnequipped();
};
