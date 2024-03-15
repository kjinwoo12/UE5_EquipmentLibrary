// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentInstance.generated.h"

class UAbilitySystemComponent;
class UEquipmentAbilitySystemManager;
struct FEquipmentGameplayAbilitySet;
struct FEquipmentGameplayEffectSet;
struct FEquipmentGameplayAttributeSet;

USTRUCT()
struct FEquipmentActorAttachmentOrder
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TSubclassOf<AActor> EquipmentActorClass;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	FName AttachSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	FTransform AttachTransform;
	
	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TArray<FName> RequiredMeshComponentTags;
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
	TArray<FEquipmentActorAttachmentOrder> EquipmentActorAttachmentOrders;

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

	void SpawnDisplayedActorsTo(USkeletalMeshComponent* AttachTargetMesh);
	void DestroyDisplayedActors();

	void GiveAbilitySystemTo(UAbilitySystemComponent* AbilitySystemComponent, UObject* SourceObject);
	void TakeAbilitySystemFrom(UAbilitySystemComponent* AbilitySystemComponent);

	virtual void OnEquipped(UEquipmentComponent* EquipmentComponent);
	virtual void OnUnequipped();

	UFUNCTION(BlueprintNativeEvent)
	void OnEquippedEvent(UEquipmentComponent* EquipmentComponent);

	UFUNCTION(BlueprintNativeEvent)
	void OnUnequippedEvent();
};
