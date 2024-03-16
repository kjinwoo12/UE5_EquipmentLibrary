// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilitySystemComponent.h"
#include "EquipmentComponent.generated.h"

EQUIPMENTLIBRARY_API DECLARE_LOG_CATEGORY_EXTERN(LogEquipmentComponent, Log, All);

class UEquipmentInstance;

UCLASS(Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent))
class EQUIPMENTLIBRARY_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	FGameplayTagContainer GameplayTagContainer;

	UPROPERTY(BlueprintReadOnly)
	TArray<USkeletalMeshComponent*> Meshes;

private:
	UPROPERTY(Replicated)
	TObjectPtr<UEquipmentInstance> PrimaryEquipmentInstance;

	UAbilitySystemComponent* AbilitySystemComponent = nullptr;

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

	UFUNCTION(BlueprintCallable)
	void Initialize(const TArray<USkeletalMeshComponent*>& TargetMeshes, 
					UAbilitySystemComponent* TargetAbilitySystemComponent, 
					FGameplayTagContainer ParentGameplayTagContainer);

	UFUNCTION(BlueprintCallable)
	UEquipmentInstance* Equip(UEquipmentInstance* EquipmentInstance);

	UFUNCTION(BlueprintCallable)
	UEquipmentInstance* UnEquip();

	UFUNCTION(Blueprintcallable)
	UEquipmentInstance* GetPrimaryEquipmentInstance();
};