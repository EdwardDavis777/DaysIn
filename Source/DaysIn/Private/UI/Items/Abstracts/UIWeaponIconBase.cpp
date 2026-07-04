//Engine imports.
#include "UI/Items/Abstracts/UIWeaponIconBase.h"


//Other imports.
#include "Weapons/Abstracts/WeaponInstance.h"
#include "Weapons/Abstracts/WeaponBase.h"



//Widget imports.
#include "UI/Items/SimpleStats/UIWeaponDurability.h"




void UUIWeaponIconBase::Init(UItemInstance* Instance)
{
	UUIItemIconBase::Init(Instance);

	if (WeaponInstance = FindAssocaitedInstance<UWeaponInstance>())
	{
		if (WeaponDurability)
		{
			WeaponDurability->InitializeWeapon(WeaponInstance);
		}
	}
}

void UUIWeaponIconBase::Init(AItemBase* RawItem)
{
	UUIItemIconBase::Init(RawItem);

	if (WeaponInstance = FindAssocaitedInstance<UWeaponInstance>())
	{
		if(WeaponDurability)
		{ 
		   WeaponDurability->InitializeWeapon(WeaponInstance);
	    }
	}
}