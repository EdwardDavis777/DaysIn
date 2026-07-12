//Engine imports.
#include "Save/Abstracts/SaveInstanceBase.h"


//Other imports.
#include "Items/Abstracts/ItemInstance.h"
#include "Items/Abstracts/Itembase.h"
#include "Spawners/Items/ItemSpawner.h"



//Archive imports.
#include "Save/SaveArchive/ProxyArchive.h"
#include "Save/SaveArchive/SaveMethods.h"





USaveInstanceBase::USaveInstanceBase()
{
	SaveName = "Un-namedSave";
}





void USaveInstanceBase::Save()
{
	if (ProxyCache.IsEmpty()) return;

	SavedPackages.Reserve(ProxyCache.Num());
	for (TPair<TObjectPtr<UItemInstance>, FSPKGInstanceBase>& Pkg : ProxyCache)
	{
		if (Pkg.Key.Get())
		{
			Arch::SerializeObject<FSPKGInstanceBase>(Pkg.Key, Pkg.Value); 
			SavedPackages.Emplace(Pkg.Value);
		}
	}
	SaveMethod::MakeSaveSlot(this, SaveName);
	ProxyCache.Empty();
}



void USaveInstanceBase::Load(UWorld* WorldContext)
{
	if (!WorldContext) return;
	
	if (LoadedSave = Cast<USaveInstanceBase>(SaveMethod::LoadSave(SaveName)))
	{
		LoadedAssets.Reserve(LoadedSave->SavedPackages.Num());
		for (auto& Pkg : LoadedSave->SavedPackages)
		{
			uint32_t Iter = LoadedAssets.Emplace(ItemSpawner::SpawnItemLazy(Pkg.ItemClass, WorldContext));
			Arch::DeSerializeObject<FSPKGInstanceBase>(LoadedAssets[Iter]->Instance(), Pkg);
		}
		PostLoadSave(WorldContext);
	}
}



/*
								Cache event functions.
*/

void USaveInstanceBase::UnProxyInstance(UItemInstance* Instance)
{
	if (!Instance) return;
	if (ProxyCache.Contains(Instance)) { ProxyCache.Remove(Instance); }
}