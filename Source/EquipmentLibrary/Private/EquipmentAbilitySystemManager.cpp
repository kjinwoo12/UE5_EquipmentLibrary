// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentAbilitySystemManager.h"
#include "AbilitySystemComponent.h"

DEFINE_LOG_CATEGORY(LogEquipmentAbilitySystemManager);

void UEquipmentAbilitySystemManager::GiveAbilityTo(UAbilitySystemComponent* AbilitySystemComponent, UObject* SourceObject, TArray<FEquipmentGameplayAbilitySet> GameplayAbilities)
{
	check(AbilitySystemComponent);
	if(!AbilitySystemComponent->IsOwnerActorAuthoritative())
	{
		return;
	}

	for(int32 AbilityIndex = 0; AbilityIndex < GameplayAbilities.Num(); AbilityIndex++)
	{
		const FEquipmentGameplayAbilitySet& GameplayAbility = GameplayAbilities[AbilityIndex];
		if(!IsValid(GameplayAbility.Ability))
		{
			UE_LOG(LogEquipmentAbilitySystemManager, Error, TEXT("GameplayAbilities[%d] on ability set [%s] is not valid."), AbilityIndex, *GetNameSafe(this));
			continue;
		}

		UGameplayAbility* AbilityCDO = GameplayAbility.Ability->GetDefaultObject<UGameplayAbility>();
		FGameplayAbilitySpec AbilitySpec(AbilityCDO, GameplayAbility.AbilityLevel);
		AbilitySpec.SourceObject = SourceObject;
		AbilitySpec.DynamicAbilityTags.AddTag(GameplayAbility.InputTag);

		const FGameplayAbilitySpecHandle AbilitySpecHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);

		GameplayAbilitySpecHandles.Add(AbilitySpecHandle);
	}
}

void UEquipmentAbilitySystemManager::TakeAbilityFrom(UAbilitySystemComponent* AbilitySystemComponent)
{
	check(AbilitySystemComponent);
	if(!AbilitySystemComponent->IsOwnerActorAuthoritative())
	{
		return;
	}

	for(const FGameplayAbilitySpecHandle& Handle : GameplayAbilitySpecHandles)
	{
		if(Handle.IsValid())
		{
			AbilitySystemComponent->ClearAbility(Handle);
		}
	}

	GameplayAbilitySpecHandles.Reset();
}

void UEquipmentAbilitySystemManager::GiveEffectTo(UAbilitySystemComponent* AbilitySystemComponent, UObject* SourceObject, TArray<FEquipmentGameplayEffectSet> GameplayEffects)
{
	check(AbilitySystemComponent);
	if(!AbilitySystemComponent->IsOwnerActorAuthoritative())
	{
		return;
	}

	for(int32 EffectIndex = 0; EffectIndex < GameplayEffects.Num(); EffectIndex++)
	{
		const FEquipmentGameplayEffectSet& GameplayEffect = GameplayEffects[EffectIndex];
		if(!IsValid(GameplayEffect.GameplayEffect))
		{
			UE_LOG(LogEquipmentAbilitySystemManager, Error, TEXT("GameplayEffects[%d] on effect set [%s] is not valid."), EffectIndex, *GetNameSafe(this));
			continue;
		}

		UGameplayEffect* GameplayEffectCDO = GameplayEffect.GameplayEffect->GetDefaultObject<UGameplayEffect>();
		FActiveGameplayEffectHandle ActiveEffectHandle = AbilitySystemComponent->ApplyGameplayEffectToSelf(
			GameplayEffectCDO,
			GameplayEffect.EffectLevel,
			AbilitySystemComponent->MakeEffectContext()
		);

		GameplayEffectHandles.Add(ActiveEffectHandle);
	}
}

void UEquipmentAbilitySystemManager::TakeEffectFrom(UAbilitySystemComponent* AbilitySystemComponent)
{
	check(AbilitySystemComponent);
	if(!AbilitySystemComponent->IsOwnerActorAuthoritative())
	{
		return;
	}

	for(const FActiveGameplayEffectHandle& Handle : GameplayEffectHandles)
	{
		if(Handle.IsValid())
		{
			AbilitySystemComponent->RemoveActiveGameplayEffect(Handle);
		}
	}

	GameplayEffectHandles.Reset();
}

void UEquipmentAbilitySystemManager::GiveAttributeTo(UAbilitySystemComponent* AbilitySystemComponent, UObject* SourceObject, TArray<FEquipmentGameplayAttributeSet> GameplayAttributes)
{
	for(int32 AttributeIndex = 0; AttributeIndex < GameplayAttributes.Num(); ++AttributeIndex)
	{
		const FEquipmentGameplayAttributeSet& GameplayAttribute = GameplayAttributes[AttributeIndex];

		if(!IsValid(GameplayAttribute.AttributeSet))
		{
			UE_LOG(LogEquipmentAbilitySystemManager, Error, TEXT("GameplayAttributes[%d] on attribute set [%s] is not valid"), AttributeIndex, *GetNameSafe(this));
			continue;
		}

		UAttributeSet* AttributeInstance = NewObject<UAttributeSet>(
			AbilitySystemComponent->GetOwner(),
			GameplayAttribute.AttributeSet
		);
		AbilitySystemComponent->AddAttributeSetSubobject(AttributeInstance);

		GameplayAttributeInstances.Add(AttributeInstance);
	}
}

void UEquipmentAbilitySystemManager::TakeAttributeFrom(UAbilitySystemComponent* AbilitySystemComponent)
{
	for(UAttributeSet* AttributeInstance : GameplayAttributeInstances)
	{
		AbilitySystemComponent->RemoveSpawnedAttribute(AttributeInstance);
	}
	GameplayAttributeInstances.Reset();
}