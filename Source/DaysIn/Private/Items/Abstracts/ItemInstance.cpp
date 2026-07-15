//Engine imports.
#include "Items/Abstracts/ItemInstance.h"

//Other imports.
#include "Items/Data/Abstracts/ItemDataAsset.h"


//Custom component imports.
#include "Items/Components/InstanceUIRuntimeComponent.h"
#include "CustomClasses/Components/Factory/GameplayComponentTemplate.h"
 

//Utility imports.
#include "SubsystemUtilitys/SubsystemUtility.h"

//Subsystem imports.
#include "Subsystems/Item/ItemEventSubsystem.h"



void UItemInstance::Initialize(UWorld* WorldContext, UItemDataAsset* ItemData)
{ 
	if (!WorldContext || !ItemData) return;   

	World = WorldContext;
	StaticItemData = ItemData;
	UIRuntimeComponent = GameplayTemplate::CreateDefaultGameplayComponent<UInstanceUIRuntimeComponent>(World,this);
	ItemEventSubsystem = SubUtility::FindSub<UItemEventSubsystem>(WorldContext);
} 



/*
								 Virtual event functions.
*/

void UItemInstance::PostOuterDeserialize()
{
	if (!ItemEventSubsystem) return;
	ItemEventSubsystem->Dispatches.PostDeserizlieEvent.Broadcast(ItemRuntimeData.SubInstancePackages,ItemRuntimeData.DeserializedInners, this);
}

void UItemInstance::PostInnerDeserialize()
{
	if (ItemRuntimeData.DeserializedInners.IsEmpty()) return;
}



/*
                                       Mutators.
*/

void UItemInstance::AddSubInstance(UObject* SubInstance, const FIntPoint& Position)
{
	if (!SubInstance || ItemRuntimeData.SubInstances.Contains(SubInstance)) return;
	ItemRuntimeData.SubInstances.Emplace(SubInstance,Position);
}

void UItemInstance::RemoveSubInstance(UObject* SubInstance)
{
	if (!SubInstance || !ItemRuntimeData.SubInstances.Contains(SubInstance)) return;
	ItemRuntimeData.SubInstances.Remove(SubInstance);
}






/*
									  Accessors.
*/

TMap<TObjectPtr<AActor>, FSPKGSubInstance>& UItemInstance::GetInners()
{
	return ItemRuntimeData.DeserializedInners;
}

TArray<FSPKGSubInstance>& UItemInstance::GetSubInstancePackages()
{
	return ItemRuntimeData.SubInstancePackages;
}

const TMap<TObjectPtr<UObject>, FIntPoint>& UItemInstance::GetSubInstances() const
{
	return  ItemRuntimeData.SubInstances;
}

TObjectPtr<UItemDataAsset>& UItemInstance::GetStaticItemData()
{
	return StaticItemData;
}

FItemRunTimeData& UItemInstance::GetItemRuntimeData()
{
	return ItemRuntimeData;
}

const FIntPoint UItemInstance::GetItemSize() const
{
	return StaticItemData->ItemUIProperties.ItemSize;
}

const FIntPoint UItemInstance::GetItemUIRotation() const
{
	return ItemRuntimeData.ItemUIRuntimeData.RotatedSize;
}

const FIntPoint UItemInstance::GetDynamicUISize() const
{
	const auto& UIData = ItemRuntimeData.ItemUIRuntimeData;
	if (UIData.bItemRotated)
	{
		return UIData.RotatedSize;
	}
	return StaticItemData->ItemUIProperties.ItemSize;
}

bool UItemInstance::bRotated()
{
	return ItemRuntimeData.ItemUIRuntimeData.bItemRotated;
}

const FText UItemInstance::GetUIName() const
{
	return StaticItemData->ItemUIProperties.UIName;
}

const EEquipTag UItemInstance::GetEquipTag() const
{
	return StaticItemData->ItemProperties.EquipTag;
}

const TSubclassOf<AItemBase>& UItemInstance::GetItemClass() const
{
	return StaticItemData->ItemProperties.ItemClass;
}

UTexture2D* UItemInstance::GetItemIcon()
{
	return StaticItemData->ItemUIProperties.Icon.Get();
}

TSubclassOf<UUIDraggableBase>& UItemInstance::GetIconClass()
{
	return StaticItemData->ItemUIProperties.IconClass;
}

TObjectPtr<UInstanceUIRuntimeComponent>& UItemInstance::GetUIRuntimeComponent()
{
	return UIRuntimeComponent;
}