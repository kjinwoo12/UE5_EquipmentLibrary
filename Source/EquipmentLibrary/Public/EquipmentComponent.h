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
private:
	UPROPERTY(Replicated)
	TObjectPtr<UEquipmentInstance> PrimaryEquipmentInstance;
	
	USkeletalMeshComponent* Mesh = nullptr;

	UAbilitySystemComponent* AbilitySystemComponent = nullptr;

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

	UFUNCTION(BlueprintCallable)
	void Initialize(USkeletalMeshComponent* TargetMesh, UAbilitySystemComponent* TargetAbilitySystemComponent);

	UFUNCTION(BlueprintCallable)
	UEquipmentInstance* Equip(UEquipmentInstance* EquipmentInstance);

	UFUNCTION(BlueprintCallable)
	UEquipmentInstance* UnEquip();
};