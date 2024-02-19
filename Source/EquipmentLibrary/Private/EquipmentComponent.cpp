// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"
#include "EquipmentInstance.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogEquipmentComponent);

UEquipmentComponent::UEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEquipmentComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, PrimaryEquipmentInstance);
}

UEquipmentInstance* UEquipmentComponent::Equip(UEquipmentInstance* EquipmentInstance)
{
	if(TargetMesh == nullptr)
	{
		UE_LOG(LogEquipmentComponent, Warning, TEXT("TargetMesh is nullptr"));
		return nullptr;
	}
	UnEquip();

	PrimaryEquipmentInstance = EquipmentInstance;
	PrimaryEquipmentInstance->SpawnEquipmentActorsTo(TargetMesh);
	PrimaryEquipmentInstance->OnEquipped();
	return PrimaryEquipmentInstance;
}

UEquipmentInstance* UEquipmentComponent::UnEquip()
{
	UEquipmentInstance* RemovedInstance = PrimaryEquipmentInstance;
	if(RemovedInstance != nullptr)
	{
		RemovedInstance->DestroyEquipmentActors();
		PrimaryEquipmentInstance = nullptr;
	}
	RemovedInstance->OnUnequipped();
	return RemovedInstance;
}