// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ControllerComponent.h"
#include "Abilities/GameplayAbility.h"
#include "EquipmentStateComponent.generated.h"

UCLASS()
class EQUIPMENTLIBRARY_API UEquipmentStateComponent : public UControllerComponent
{
	GENERATED_BODY()

public:
	UEquipmentStateComponent(const FObjectInitializer& ObjectInitializer);

	virtual void TickComponent(float DeltaSeconds,
							   ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;
};
