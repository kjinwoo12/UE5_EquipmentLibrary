// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimatedEquipmentInstance.h"
#include "EquipmentComponent.h"

void UAnimatedEquipmentInstance::OnEquipped(UEquipmentComponent* EquipmentComponent)
{
	AnimatedMeshes = EquipmentComponent->Meshes;
	TagContainer = EquipmentComponent->GameplayTagContainer;

	for(USkeletalMeshComponent* AnimatedMesh : AnimatedMeshes)
	{
		TSubclassOf<UAnimInstance> AnimClass = EquippedAnimLayer.SelectBestLayer(AnimatedMesh, TagContainer);
		if(AnimClass)
		{
			AnimatedMesh->LinkAnimClassLayers(AnimClass);
		}
		AnimatedMesh->GetAnimInstance()->Montage_Play(EquipMontage);
	}

	Super::OnEquipped(EquipmentComponent);
}

void UAnimatedEquipmentInstance::OnUnequipped()
{
	for(USkeletalMeshComponent* AnimatedMesh : AnimatedMeshes)
	{
		TSubclassOf<UAnimInstance> AnimClass = UnequippedAnimLayer.SelectBestLayer(AnimatedMesh, TagContainer);
		if(AnimClass)
		{
			AnimatedMesh->LinkAnimClassLayers(AnimClass);
		}
		AnimatedMesh->GetAnimInstance()->Montage_Play(UnequipMontage);
	}
	Super::OnUnequipped();
}