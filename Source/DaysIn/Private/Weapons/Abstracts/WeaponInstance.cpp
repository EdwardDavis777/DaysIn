//Engine imports.
#include "Weapons/Abstracts/WeaponInstance.h"


//Other imports.
#include "Weapons/Data/WeaponDataAsset.h"


void UWeaponInstance::Initialize(UWorld* WorldContext, UItemDataAsset* ItemData)
{
	Super::Initialize(WorldContext, ItemData); 
	StaticWeaponData = GetData<UWeaponDataAsset>(); 
}



/*
									Accessors.
*/

TObjectPtr<UWeaponDataAsset>& UWeaponInstance::GetStaticWeaponData()
{
	return StaticWeaponData;
}

FWepRunTimeData& UWeaponInstance::GetRuntimeData()
{
	return WeaponRuntimeData;
}

FWepRunTimeStats& UWeaponInstance::GetRuntimeStats()
{
	return WeaponRuntimeData.WeaponRunTimeStats;
}
