//Engine imports.
#include "UI/Player/EquipSlots/UIWeaponSlotBase.h"



//Other imports.
#include "Weapons/Abstracts/WeaponInstance.h"
#include "Weapons/Abstracts/WeaponBase.h"



void UUIWeaponSlotBase::StoreItem(AItemBase* Item, const FIntPoint& Position)
{
    UUIEquipSlotBase::StoreItem(Item,Position);

    if(StoredWeapon = FindAssocaitedInstance<UWeaponInstance>())
    { 
       SlotData.bOccupied = true;
       Item->Pickup();
    }
}



bool UUIWeaponSlotBase::StoreDropped(UItemInstance* ItemInstance)
{
    if(UUIEquipSlotBase::StoreDropped(ItemInstance))
    { 
       StoredWeapon = FindAssocaitedInstance<UWeaponInstance>();
       SlotData.bOccupied = true;
       return true;
    }
    return false;
}


void UUIWeaponSlotBase::RemoveStored(TObjectPtr<UItemInstance>& AssociatedInstance)
{
    UUIEquipSlotBase::RemoveStored(AssociatedInstance);

    StoredWeapon = nullptr;
    SlotData.bOccupied = false;
}