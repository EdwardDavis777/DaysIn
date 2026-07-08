//Engine imports.
#include "PlayerStorage/Abstracts/CollectableStorageBase.h"


//Other imports.
#include "PlayerStorage/Data/CollectableStorageDataAsset.h"
#include "PlayerStorage/Abstracts/CollectableStorageInstance.h"


//Custom components.
#include "Items/Components/ItemPhysicsComponent.h"


 

void ACollectableStorageBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ItemDataAsset)
	{
		CollectableStorageDataAsset = GetData<UCollectableStorageDataAsset>();
		CollectableStorageInstance = GetInstance<UCollectableStorageInstance>();
	}
}



/*
								         Virtual event functions.
*/

void ACollectableStorageBase::Pickup()
{
	Destroy();
}

void ACollectableStorageBase::Drop(UItemInstance* Instance)
{
	Super::Drop(Instance);

	if (auto* StorageInst = GetInstance<UCollectableStorageInstance>())
	{
		CollectableStorageDataAsset = StorageInst->GetStaticStorageData();
		CollectableStorageInstance = StorageInst;
		ItemPhysicsComponent->ApplyCollisionAndPhysicsButIgnorePawn(ItemMesh, CollectableStorageDataAsset->ItemPhysicsProperties);
	}
} 