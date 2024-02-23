// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "EquipmentAnimLayerSelector.generated.h"


USTRUCT(BlueprintType)
struct FEquipmentAnimLayerSelectionRule
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAnimInstance> Layer;

	UPROPERTY(EditAnywhere, blueprintReadWrite)
	FGameplayTagContainer RequiredTags;
};


UCLASS(Blueprintable, BlueprintType)
class UEquipmentAnimLayerSelector : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	TArray<FEquipmentAnimLayerSelectionRule> LayerRules;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAnimInstance> DefaultLayer;

	UFUNCTION(BlueprintCallable)
	TSubclassOf<UAnimInstance> SelectBestLayer(const FGameplayTagContainer& CosmeticTags) const;
};