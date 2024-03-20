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


void UEquipmentComponent::BeginPlay()
{
	AActor* OwningActor = Cast<AActor>(GetOuter());
	if(OwningActor)
	{
		AbilitySystemComponent = OwningActor->GetComponentByClass<UAbilitySystemComponent>();
	}
}

UEquipmentInstance* UEquipmentComponent::Equip(UEquipmentInstance* EquipmentInstance)
{
	UnEquip();
	PrimaryEquipmentInstance = EquipmentInstance;

	AActor* OwningActor = Cast<AActor>(GetOuter());
	TSet<UActorComponent*> AllComponents = OwningActor->GetComponents();
	for(UActorComponent* Component : AllComponents)
	{
		if(USkeletalMeshComponent* DisplayingActorParentMesh = Cast<USkeletalMeshComponent>(Component))
		{
			PrimaryEquipmentInstance->SpawnDisplayedActorsTo(DisplayingActorParentMesh);
		}
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
		if(AbilitySystemComponent)
		{
			RemovedInstance->TakeAbilitySystemFrom(AbilitySystemComponent);
		}
		RemovedInstance->DestroyDisplayedActors();
		PrimaryEquipmentInstance = nullptr;
		RemovedInstance->OnUnequipped();
	}
	return RemovedInstance;
}

UEquipmentInstance* UEquipmentComponent::GetPrimaryEquipmentInstance()
{
	return PrimaryEquipmentInstance;
}