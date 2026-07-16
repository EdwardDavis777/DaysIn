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
	SavedPackages.Empty();
	SavedPackages.Reserve(ProxyCache.Num());
	for (TPair<TObjectPtr<UItemInstance>, FSPKGInstanceBase>& Pkg : ProxyCache)
	{
		if (Pkg.Key.Get())
		{
			SerializeRecursive(Pkg.Key);
			Arch::SerializeObject<FSPKGInstanceBase>(Pkg.Key, Pkg.Value);
			SavedPackages.Emplace(Pkg.Value);	
		}
	}
	SaveMethod::MakeSaveSlot(this, SaveName);
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
							    Serialize event functions.
*/

void USaveInstanceBase::SerializeRecursive(UItemInstance* OuterInstance)
{
	if (!OuterInstance) return;

	OuterInstance->GetSubInstancePackages().Reserve(OuterInstance->GetSubInstances().Num());
	OuterInstance->GetSubInstancePackages().Reset();

	for (const TPair<TObjectPtr<UObject>, FIntPoint>& SubInstance : OuterInstance->GetSubInstances())
	{
		if (!SubInstance.Key.Get()) continue;

		auto* OuterItem = Cast<UItemInstance>(SubInstance.Key.Get());
		if (!OuterItem) continue;

		FSPKGSubInstance NewSubPackage;
		NewSubPackage.ItemClass = OuterItem->GetItemClass();
		NewSubPackage.Position = SubInstance.Value;

		SerializeRecursive(OuterItem);
	
		Arch::SerializeObject(OuterItem, NewSubPackage);
		OuterInstance->GetSubInstancePackages().Emplace(NewSubPackage);
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