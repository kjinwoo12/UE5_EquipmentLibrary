// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimatedEquipmentInstance.h"
#include "EquipmentComponent.h"

void UAnimatedEquipmentInstance::OnEquipped(UEquipmentComponent* EquipmentComponent)
{
	AActor* OwningActor = Cast<AActor>(GetOuter());
	TSet<UActorComponent*> AllComponents = OwningActor->GetComponents();
	AnimatedMeshes.Empty();
	for(UActorComponent* Component : AllComponents)
	{
		if(USkeletalMeshComponent* AnimatedMesh = Cast<USkeletalMeshComponent>(Component))
		{
			TSubclassOf<UAnimInstance> AnimClass = EquippedAnimLayer.SelectBestLayer(AnimatedMesh, TagContainer);
			if(AnimClass)
			{
				AnimatedMesh->LinkAnimClassLayers(AnimClass);
			}
			AnimatedMesh->GetAnimInstance()->Montage_Play(EquipMontage);
			AnimatedMeshes.Add(AnimatedMesh);
		}
	}

	TagContainer = EquipmentComponent->GameplayTagContainer;

	Super::OnEquipped(EquipmentComponent);
}

void UAnimatedEquipmentInstance::OnUnequipped()
{
	for(USkeletalMeshComponent* AnimatedMesh : AnimatedMeshes)
	{
		if(!AnimatedMesh)
		{
			continue;
		}

		TSubclassOf<UAnimInstance> AnimClass = UnequippedAnimLayer.SelectBestLayer(AnimatedMesh, TagContainer);
		if(AnimClass)
		{
			AnimatedMesh->LinkAnimClassLayers(AnimClass);
		}
		AnimatedMesh->GetAnimInstance()->Montage_Play(UnequipMontage);
	}
	AnimatedMeshes.Empty();
	Super::OnUnequipped();
}