// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentInstance.h"
#include "EquipmentAnimLayer.h"
#include "AnimatedEquipmentInstance.generated.h"

/**
 * 
 */
UCLASS()
class EQUIPMENTLIBRARY_API UAnimatedEquipmentInstance : public UEquipmentInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FEquipmentAnimLayer EquippedAnimLayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FEquipmentAnimLayer UnequippedAnimLayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* UnequipMontage;

private:
	TArray<USkeletalMeshComponent*> AnimatedMeshes;
	FGameplayTagContainer TagContainer;

public:
	virtual void OnEquipped(UEquipmentComponent* EquipmentComponent) override;

	virtual void OnUnequipped() override;
};
