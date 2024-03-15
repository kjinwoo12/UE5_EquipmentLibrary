// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentStateComponent.h"
#include "EquipmentInstance.h"
#include "EquipmentTickInterface.h"

UEquipmentStateComponent::UEquipmentStateComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetIsReplicatedByDefault(true);

	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UEquipmentStateComponent::TickComponent(float DeltaSeconds,
											 ELevelTick TickType,
											 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaSeconds, TickType, ThisTickFunction);

	if(APawn* Pawn = GetPawn<APawn>())
	{
		if(UEquipmentComponent* EquipmentComponent = Pawn->FindComponentByClass<UEquipmentComponent>())
		{
			if(IEquipmentTickInterface* EquipmentTickInterface = Cast<IEquipmentTickInterface>(EquipmentComponent))
			{
				EquipmentTickInterface->Tick(DeltaSeconds);
			}
		}
	}
}