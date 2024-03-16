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

void UEquipmentComponent::Initialize(const TArray<USkeletalMeshComponent*>& TargetMesh,
									 UAbilitySystemComponent* TargetAbilitySystemComponent, 
									 FGameplayTagContainer ParentGameplayTagContainer)
{
	Meshes = TargetMesh;
	AbilitySystemComponent = TargetAbilitySystemComponent;
	GameplayTagContainer = ParentGameplayTagContainer;
}

UEquipmentInstance* UEquipmentComponent::Equip(UEquipmentInstance* EquipmentInstance)
{
	UnEquip();
	PrimaryEquipmentInstance = EquipmentInstance;
	for(USkeletalMeshComponent* Mesh : Meshes)
	{
		PrimaryEquipmentInstance->SpawnDisplayedActorsTo(Mesh);
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
		RemovedInstance->DestroyDisplayedActors();
		RemovedInstance->TakeAbilitySystemFrom(AbilitySystemComponent);
		PrimaryEquipmentInstance = nullptr;
		RemovedInstance->OnUnequipped();
	}
	return RemovedInstance;
}

UEquipmentInstance* UEquipmentComponent::GetPrimaryEquipmentInstance()
{
	return PrimaryEquipmentInstance;
}