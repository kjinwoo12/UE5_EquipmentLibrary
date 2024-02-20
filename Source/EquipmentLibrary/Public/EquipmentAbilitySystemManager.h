// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentGameplayAbilitySet.h"
#include "EquipmentGameplayEffectSet.h"
#include "EquipmentGameplayAttributeSet.h"
#include "EquipmentAbilitySystemManager.generated.h"

EQUIPMENTLIBRARY_API DECLARE_LOG_CATEGORY_EXTERN(LogEquipmentAbilitySystemManager, Log, All);



/**
 * 
 */
UCLASS(BlueprintType)
class EQUIPMENTLIBRARY_API UEquipmentAbilitySystemManager : public UObject
{
	GENERATED_BODY()

private:
	TArray<FGameplayAbilitySpecHandle> GameplayAbilitySpecHandles;
	TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;
	TArray<TObjectPtr<UAttributeSet>> GameplayAttributeInstances;

public:
	void GiveAbilityTo(UAbilitySystemComponent* AbilitySystemComponent, UObject* SourceObject, TArray<FEquipmentGameplayAbilitySet> GameplayAbilities);
	void TakeAbilityFrom(UAbilitySystemComponent* AbilitySystemComponent);

	void GiveEffectTo(UAbilitySystemComponent* AbilitySystemComponent, UObject* SourceObject, TArray<FEquipmentGameplayEffectSet> GameplayEffects);
	void TakeEffectFrom(UAbilitySystemComponent* AbilitySystemComponent);

	void GiveAttributeTo(UAbilitySystemComponent* AbilitySystemComponent, UObject* SourceObject, TArray<FEquipmentGameplayAttributeSet> GameplayAttributes);
	void TakeAttributeFrom(UAbilitySystemComponent* AbilitySystemComponent);
};