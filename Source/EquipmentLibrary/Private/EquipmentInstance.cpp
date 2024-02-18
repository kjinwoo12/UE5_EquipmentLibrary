// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentInstance.h"
#include "Net/UnrealNetwork.h"
#include "EquipmentActorEvent.h"
#include "AbilitySystemComponent.h"

DEFINE_LOG_CATEGORY(LogEquipmentInstance);

void UEquipmentInstance::BeginDestroy()
{
	DestroyEquipmentActors();
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
	GiveAbilityTo(AbilitySystemComponent, SourceObject);
	GiveEffectTo(AbilitySystemComponent, SourceObject);
	GiveAttributeTo(AbilitySystemComponent, SourceObject);
}

void UEquipmentInstance::TakeAbilitySystemFrom(UAbilitySystemComponent* AbilitySystemComponent)
{
	TakeAbilityFrom(AbilitySystemComponent);
	TakeEffectFrom(AbilitySystemComponent);
	TakeAttributeFrom(AbilitySystemComponent);
}

void UEquipmentInstance::GiveAbilityTo(UAbilitySystemComponent* AbilitySystemComponent, UObject* SourceObject)
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
			UE_LOG(LogEquipmentInstance, Error, TEXT("GameplayAbilities[%d] on ability set [%s] is not valid."), AbilityIndex, *GetNameSafe(this));
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

void UEquipmentInstance::TakeAbilityFrom(UAbilitySystemComponent* AbilitySystemComponent)
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

void UEquipmentInstance::GiveEffectTo(UAbilitySystemComponent* AbilitySystemComponent, UObject* SourceObject)
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
			UE_LOG(LogEquipmentInstance, Error, TEXT("GameplayEffects[%d] on effect set [%s] is not valid."), EffectIndex, *GetNameSafe(this));
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

void UEquipmentInstance::TakeEffectFrom(UAbilitySystemComponent* AbilitySystemComponent)
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

void UEquipmentInstance::GiveAttributeTo(UAbilitySystemComponent* AbilitySystemComponent, UObject* SourceObject)
{
	for(int32 AttributeIndex = 0; AttributeIndex < GameplayAttributes.Num(); ++AttributeIndex)
	{
		const FEquipmentGameplayAttributeSet& GameplayAttribute = GameplayAttributes[AttributeIndex];

		if(!IsValid(GameplayAttribute.AttributeSet))
		{
			UE_LOG(LogEquipmentInstance, Error, TEXT("GameplayAttributes[%d] on attribute set [%s] is not valid"), AttributeIndex, *GetNameSafe(this));
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

void UEquipmentInstance::TakeAttributeFrom(UAbilitySystemComponent* AbilitySystemComponent)
{
	for(UAttributeSet* AttributeInstance : GameplayAttributeInstances)
	{
		AbilitySystemComponent->RemoveSpawnedAttribute(AttributeInstance);
	}
	GameplayAttributeInstances.Reset();
}