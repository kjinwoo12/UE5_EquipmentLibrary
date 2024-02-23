// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentAnimLayerSelector.h"

TSubclassOf<UAnimInstance> UEquipmentAnimLayerSelector::SelectBestLayer(const FGameplayTagContainer& CosmeticTags) const
{
	for(const FEquipmentAnimLayerSelectionRule& Rule : LayerRules)
	{
		if((Rule.Layer != nullptr) && CosmeticTags.HasAll(Rule.RequiredTags))
		{
			return Rule.Layer;
		}
	}

	return DefaultLayer;
}