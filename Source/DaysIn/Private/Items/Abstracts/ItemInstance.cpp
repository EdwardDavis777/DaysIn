//Engine imports.
#include "Items/Abstracts/ItemInstance.h"

//Other imports.
#include "Items/Data/Abstracts/ItemDataAsset.h"



void UItemInstance::Initialize(UWorld* WorldContext, UItemDataAsset* ItemData)
{ 
	if (!WorldContext || !ItemData) return;   

	World = WorldContext;
	StaticItemData = ItemData;
} 




/*
									  Accessors.
*/

TObjectPtr<UItemDataAsset>& UItemInstance::GetStaticItemData()
{
	return StaticItemData;
}

const FIntPoint UItemInstance::GetItemSize() const
{
	return StaticItemData->ItemUIProperties.ItemSize;
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