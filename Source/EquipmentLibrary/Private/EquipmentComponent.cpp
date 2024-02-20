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

void UEquipmentComponent::Initialize(USkeletalMeshComponent* TargetMesh, UAbilitySystemComponent* TargetAbilitySystemComponent)
{
	Mesh = TargetMesh;
	AbilitySystemComponent = TargetAbilitySystemComponent;
}

UEquipmentInstance* UEquipmentComponent::Equip(UEquipmentInstance* EquipmentInstance)
{
	UnEquip();
	PrimaryEquipmentInstance = EquipmentInstance;
	if(Mesh != nullptr)
	{
		PrimaryEquipmentInstance->SpawnEquipmentActorsTo(Mesh);
	}
	if(AbilitySystemComponent != nullptr)
	{
		PrimaryEquipmentInstance->GiveAbilitySystemTo(AbilitySystemComponent, GetOwner());
	}
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
		RemovedInstance->OnUnequipped();
	}
	return RemovedInstance;
}