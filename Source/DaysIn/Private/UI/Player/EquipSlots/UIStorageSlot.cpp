//Engine imports.
#include "UI/Player/EquipSlots/UIStorageSlot.h"



//Other imports.
#include "PlayerStorage/Abstracts/CollectableStorageInstance.h"
#include "PlayerStorage/Abstracts/CollectableStorageBase.h"
#include "PlayerStorage/Components/CollectableStorageUIComponent.h"



/*
								   Virtual event functions.
*/

void UUIStorageSlot::StoreItem(AItemBase* Item)
{
	Super::StoreItem(Item);

	if (CollectableStorageInstance = FindAssocaitedInstance<UCollectableStorageInstance>())
	{
		SlotData.bOccupied = true;
		Item->Pickup();
	}
}

bool UUIStorageSlot::StoreDropped(UItemInstance* ItemInstance)
{
	if (Super::StoreDropped(ItemInstance))
	{
		CollectableStorageInstance = FindAssocaitedInstance<UCollectableStorageInstance>();
		CollectableStorageInstance->GetStorageUIComponent()->RebuildInRegion();
		SlotData.bOccupied = true;
		return true;
	}
	return false;
}

void UUIStorageSlot::RemoveStored(TObjectPtr<UItemInstance>& AssocaitedInstance)
{
	Super::RemoveStored(AssocaitedInstance);

	CollectableStorageInstance->GetStorageUIComponent()->ClearInventory();
	CollectableStorageInstance = nullptr;
	SlotData.bOccupied = false;
}