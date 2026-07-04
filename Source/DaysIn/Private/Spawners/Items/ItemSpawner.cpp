//Engine imports.
#include "Spawners/Items/ItemSpawner.h"

//Other imports.
#include "Items/Abstracts/ItemBase.h"
#include "Items/Abstracts/ItemInstance.h"

 

namespace ItemSpawner
{
	AItemBase* SpawnItemLazy(const TSubclassOf<AItemBase>& ItemClass,UWorld* WorldContext)
	{
		if (!ItemClass || !WorldContext) return nullptr;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		FVector SpawnLoc = FVector::ZeroVector;
		FRotator SpawnRot = FRotator::ZeroRotator;

		if (auto* SpawnedItem = WorldContext->SpawnActor<AItemBase>(ItemClass, SpawnLoc, SpawnRot, SpawnParams))
		{
			return SpawnedItem;
		}
		return nullptr;
	}
}