//Engine imports.
#include "Save/Abstracts/SaveGenericInner.h"


//Other imports.
#include "Items/Abstracts/ItemInstance.h"
#include "Items/Abstracts/ItemBase.h"
#include "Save/Packages/Objects/Abstracts/SPKGSubInstance.h"


//Spawner imports.
#include "Spawners/Items/ItemSpawner.h"


//Archive imports.
#include "Save/SaveArchive/ProxyArchive.h"



/*
							           Load event functions.
*/

void USaveGenericInner::DeserializeInners(const TArray<FSPKGSubInstance>& SavePackages, TMap<TObjectPtr<AActor>, FSPKGSubInstance>& SentBackInners, UItemInstance* OuterInstance,UWorld* WorldContext)
{
	if (!OuterInstance) return;

	SentBackInners.Empty();
	SentBackInners.Reserve(SavePackages.Num());
	for (const auto& Pkg : SavePackages)
	{
		auto* NewItem = ItemSpawner::SpawnInnerItem(Pkg, WorldContext);
		if (!NewItem || !NewItem->Instance()) continue;

		Arch::DeSerializeObject<FSPKGSubInstance>(NewItem->Instance(), Pkg);
		SentBackInners.Emplace(NewItem,Pkg);

		if (!NewItem->Instance()->GetSubInstancePackages().IsEmpty()) 
		{
			DeserializeInners(NewItem->Instance()->GetSubInstancePackages(),NewItem->Instance()->GetInners(), NewItem->Instance(), WorldContext);
		}
	}
	OuterInstance->PostInnerDeserialize();
}