//Engine imports.
#include "PlayerStorage/Abstracts/CollectableStorageInstance.h"


//Other imports.
#include "PlayerStorage/Data/CollectableStorageDataAsset.h"

 
//Custom components.
#include "PlayerStorage/Components/CollectableStorageUIComponent.h"
#include "PlayerStorage/Components/StorageInventoryComponent.h"
#include "CustomClasses/Components/Factory/GameplayComponentTemplate.h"





void UCollectableStorageInstance::Initialize(UWorld* WorldContext, UItemDataAsset* ItemData)
{
	Super::Initialize(WorldContext, ItemData);
	
	StaticStorageData = GetData<UCollectableStorageDataAsset>();
	CollectableStorageUIComponent = GameplayTemplate::CreateDefaultGameplayComponent<UCollectableStorageUIComponent>(World, this);
	StorageInventoryComponent = GameplayTemplate::CreateDefaultGameplayComponent<UStorageInventoryComponent>(World, this);
}



/*
										    Accessors.
*/

TObjectPtr<UCollectableStorageDataAsset>& UCollectableStorageInstance::GetStaticStorageData()
{
	return StaticStorageData;
}

TObjectPtr<UCollectableStorageUIComponent>& UCollectableStorageInstance::GetStorageUIComponent()
{
	return CollectableStorageUIComponent;
}

TObjectPtr<UStorageInventoryComponent>& UCollectableStorageInstance::GetInventoryComponent()
{
	return StorageInventoryComponent;
}

TSubclassOf<UUICollectableStorageInventory>& UCollectableStorageInstance::GetInventoryClass()
{
	return StaticStorageData->CollectableStorageUIProperties.InventoryWidgetClass;
}

const FIntPoint& UCollectableStorageInstance::GetSize() const
{
	return StaticStorageData->CollectableStorageProperties.StorageSize;
}