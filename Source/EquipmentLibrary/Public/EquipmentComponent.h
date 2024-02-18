// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"

EQUIPMENTLIBRARY_API DECLARE_LOG_CATEGORY_EXTERN(LogEquipmentComponent, Log, All);

class UEquipmentInstance;

UCLASS()
class EQUIPMENTLIBRARY_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(Replicated)
	TObjectPtr<UEquipmentInstance> PrimaryEquipmentInstance;

public:
	UPROPERTY(BLueprintReadWrite)
	USkeletalMeshComponent* TargetMesh = nullptr;

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

	UFUNCTION(BlueprintCallable)
	UEquipmentInstance* Equip(UEquipmentInstance* EquipmentInstance);

	UFUNCTION(BlueprintCallable)
	UEquipmentInstance* UnEquip();
};