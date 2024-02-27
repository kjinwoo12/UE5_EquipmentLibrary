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

void UEquipmentComponent::Initialize(USkeletalMeshComponent* TargetMesh, 
									 UAbilitySystemComponent* TargetAbilitySystemComponent, 
									 FGameplayTagContainer ParentGameplayTagContainer)
{
	Mesh = TargetMesh;
	AbilitySystemComponent = TargetAbilitySystemComponent;
	GameplayTagContainer = ParentGameplayTagContainer;
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
	PrimaryEquipmentInstance->OnEquipped(this);
	return PrimaryEquipmentInstance;
}

UEquipmentInstance* UEquipmentComponent::UnEquip()
{	
	UEquipmentInstance* RemovedInstance = PrimaryEquipmentInstance;
	if(RemovedInstance != nullptr)
	{
		RemovedInstance->DestroyEquipmentActors();
		RemovedInstance->TakeAbilitySystemFrom(AbilitySystemComponent);
		PrimaryEquipmentInstance = nullptr;
		RemovedInstance->OnUnequipped();
	}
	return RemovedInstance;
}