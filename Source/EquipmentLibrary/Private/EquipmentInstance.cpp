// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentInstance.h"
#include "Net/UnrealNetwork.h"
#include "EquipmentActorEvent.h"
#include "EquipmentAbilitySystemManager.h"

UEquipmentInstance::UEquipmentInstance()
{
	EquipmentAbilitySystemManager = NewObject<UEquipmentAbilitySystemManager>();
}

void UEquipmentInstance::SpawnEquipmentActorsTo(USkeletalMeshComponent* AttachTargetMesh)
{
	for(FEquipmentActorSpawnOrder Order : SpawningActorOrders)
	{
		AActor* SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(
			Order.EquipmentActorClass,
			FTransform::Identity, 
			AttachTargetMesh->GetOwner()
		);
		SpawnedActor->FinishSpawning(FTransform::Identity, /*bIsDefaultTransform=*/ true);
		SpawnedActor->SetActorRelativeTransform(Order.AttachTransform);
		SpawnedActor->AttachToComponent(AttachTargetMesh, FAttachmentTransformRules::KeepRelativeTransform, Order.AttachSocket);
		SpawnedEquipmentActors.Add(SpawnedActor);
		IEquipmentActorEvent::Execute_OnEquipped(SpawnedActor);
	}
}

void UEquipmentInstance::DestroyEquipmentActors()
{
	for(TObjectPtr<AActor> SpawnedActor : SpawnedEquipmentActors)
	{
		IEquipmentActorEvent::Execute_OnUnequipped(SpawnedActor);
		SpawnedEquipmentActors.Remove(SpawnedActor);
		SpawnedActor->Destroy();
	}
}

void UEquipmentInstance::GiveAbilitySystemTo(UAbilitySystemComponent* AbilitySystemComponent, UObject* SourceObject)
{
	EquipmentAbilitySystemManager->GiveAbilityTo(AbilitySystemComponent, SourceObject, GameplayAbilities);
	EquipmentAbilitySystemManager->GiveEffectTo(AbilitySystemComponent, SourceObject, GameplayEffects);
	EquipmentAbilitySystemManager->GiveAttributeTo(AbilitySystemComponent, SourceObject, GameplayAttributes);
}

void UEquipmentInstance::TakeAbilitySystemFrom(UAbilitySystemComponent* AbilitySystemComponent)
{
	EquipmentAbilitySystemManager->TakeAbilityFrom(AbilitySystemComponent);
	EquipmentAbilitySystemManager->TakeEffectFrom(AbilitySystemComponent);
	EquipmentAbilitySystemManager->TakeAttributeFrom(AbilitySystemComponent);
}

void UEquipmentInstance::OnEquipped_Implementation()
{

}

void UEquipmentInstance::OnUnequipped_Implementation()
{

}