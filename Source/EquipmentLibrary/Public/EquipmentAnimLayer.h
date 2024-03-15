// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "EquipmentAnimLayer.generated.h"


USTRUCT(BlueprintType)
struct FEquipmentAnimLayerSelectionRule
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAnimInstance> Layer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer RequiredGameplayTags;

	UPROPERTY(EditDefaultsOnly)
	TArray<FName> RequiredMeshComponentTags;
};


USTRUCT(BlueprintType)
struct FEquipmentAnimLayer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	TArray<FEquipmentAnimLayerSelectionRule> LayerRules;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAnimInstance> DefaultLayer;

	TSubclassOf<UAnimInstance> SelectBestLayer(const USkeletalMeshComponent* AnimatedMesh, 
											   const FGameplayTagContainer& CosmeticTags) const;
};