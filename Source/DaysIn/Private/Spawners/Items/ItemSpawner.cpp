//Engine imports.
#include "Spawners/Items/ItemSpawner.h"


//Data imports.
#include "Save/Packages/Objects/Abstracts/SPKGSubInstance.h"


//Other imports.
#include "Items/Abstracts/ItemBase.h"
#include "Items/Abstracts/ItemInstance.h"

 

namespace ItemSpawner
{
	AItemBase* SpawnItemLazy(const TSubclassOf<AItemBase>& ItemClass,UWorld* WorldContext)
	{
		if (!ItemClass || !WorldContext) return nullptr;

		const FEmptyConfig Default;
		if (auto* SpawnedItem = WorldContext->SpawnActor<AItemBase>(ItemClass, Default.SpawnLoc, Default.SpawnRot, Default.SpawnParams))
		{
			return SpawnedItem;
		}
		return nullptr;
	}
    
	AItemBase* SpawnInnerItem(const FSPKGSubInstance& InnerPackage,UWorld* WorldContext)
	{
		if (!InnerPackage.ItemClass || !WorldContext) return nullptr;

		const FEmptyConfig Default;
		if (auto* SpawnedItem = WorldContext->SpawnActor<AItemBase>(InnerPackage.ItemClass, Default.SpawnLoc, Default.SpawnRot, Default.SpawnParams))
		{
			return SpawnedItem;
		}
		return nullptr;
	}
}