//Engine imports.
#include "PlayerStorage/Components/CollectableStorageSaveComponent.h"


//Other imports.
#include "PlayerStorage/Abstracts/CollectableStorageInstance.h"
#include "Spawners/Items/ItemSpawner.h"
#include "PlayerStorage/Components/StorageInventoryComponent.h"
#include "Items/Abstracts/ItemBase.h"



//Utility imports.
#include "SubsystemUtilitys/SubsystemUtility.h"

//Subsystem imports. 
#include "Subsystems/Systems/Inventory/StorageInventorySubsystem.h"



void UCollectableStorageSaveComponent::Initialize(UWorld* WorldContext, UObject* OwnerObject)
{
	Super::Initialize(WorldContext, OwnerObject);
	
	StorageInstance = GetOwner<UCollectableStorageInstance>();
	InventorySubsystem = SubUtility::FindSub<UStorageInventorySubsystem>(WorldContext);
	BindDelegates();
}


void UCollectableStorageSaveComponent::BindDelegates()
{
	if (!InventorySubsystem) return;

	InventorySubsystem->StorageDispatches.ItemAddedEvent.AddUObject(this, &UCollectableStorageSaveComponent::AddSubInstance);
	InventorySubsystem->StorageDispatches.ItemRemovedEvent.AddUObject(this, &UCollectableStorageSaveComponent::RemoveSubInstance);
}


/*
								   Load event functions.
*/

void UCollectableStorageSaveComponent::LoadSavedObjects(TMap<TObjectPtr<AActor>, FSPKGSubInstance>& InnerItems)
{
	if (InnerItems.IsEmpty() || !StorageInstance) return;

	for (auto& InnerObject : InnerItems)
	{
		auto* Item = Cast<AItemBase>(InnerObject.Key);
		if (!Item) continue;
		StorageInstance->GetInventoryComponent()->bCheckAndStore(Item, InnerObject.Value.Position);
	}
	InnerItems.Empty();
}



/*
								  Runtime cache functions.
*/
 
void UCollectableStorageSaveComponent::AddSubInstance(UObject* AssocaitedStorage, UObject* AddedInstance, const FIntPoint& Position)
{
	if (!AddedInstance || !StorageInstance || StorageInstance != AssocaitedStorage) return;
	StorageInstance->AddSubInstance(AddedInstance, Position);
}

void UCollectableStorageSaveComponent::RemoveSubInstance(UObject* AssocaitedStorage, UObject* RemovedInstance)
{
	if (!RemovedInstance || !StorageInstance || StorageInstance != AssocaitedStorage) return;
	StorageInstance->RemoveSubInstance(RemovedInstance);
}