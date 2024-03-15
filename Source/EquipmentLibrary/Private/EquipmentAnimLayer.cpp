// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentAnimLayer.h"

TSubclassOf<UAnimInstance> FEquipmentAnimLayer::SelectBestLayer(const USkeletalMeshComponent* AnimatedMesh, const FGameplayTagContainer& CosmeticTags) const
{
	for(FEquipmentAnimLayerSelectionRule Rule : LayerRules)
	{
		bool bHasAllComponentTag = true;
		for(FName RequiredComponentTag : Rule.RequiredMeshComponentTags)
		{
			if(!AnimatedMesh->ComponentHasTag(RequiredComponentTag))
			{
				bHasAllComponentTag = false;
				break;
			}
		}

		bool bHasAllGameplayTag = CosmeticTags.HasAll(Rule.RequiredGameplayTags);
		if((Rule.Layer != nullptr) && bHasAllGameplayTag && bHasAllComponentTag)
		{
			return Rule.Layer;
		}
	}

	return DefaultLayer;
}