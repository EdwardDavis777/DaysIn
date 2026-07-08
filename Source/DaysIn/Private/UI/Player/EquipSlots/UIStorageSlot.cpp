//Engine imports.
#include "UI/Player/EquipSlots/UIStorageSlot.h"



//Other imports.
#include "PlayerStorage/Abstracts/CollectableStorageInstance.h"
#include "PlayerStorage/Abstracts/CollectableStorageBase.h"
#include "PlayerStorage/Components/CollectableStorageUIComponent.h"
 

//Subsystem imports. 
#include "Subsystems/Player/PlayerEquipmentSubsystem.h"


/* 
								   Virtual event functions.
*/

void UUIStorageSlot::StoreItem(AItemBase* Item, const FIntPoint& Position)
{
	UUIEquipSlotBase::StoreItem(Item, Position);

	if (CollectableStorageInstance = FindAssocaitedInstance<UCollectableStorageInstance>())
	{
		PlayerEquipmentSubsystem->PlayerEquipmentDispatches.StorageAdded.Broadcast(CollectableStorageInstance);
		SlotData.bOccupied = true;
		Item->Pickup();
	}
}

bool UUIStorageSlot::StoreDropped(UItemInstance* ItemInstance, const FIntPoint& Position)
{
	if (UUIEquipSlotBase::StoreDropped(ItemInstance))
	{
		if (CollectableStorageInstance = FindAssocaitedInstance<UCollectableStorageInstance>())
		{
			PlayerEquipmentSubsystem->PlayerEquipmentDispatches.StorageAdded.Broadcast(CollectableStorageInstance);
			SlotData.bOccupied = true;
			return true;
		}
	}
	return false;
}

void UUIStorageSlot::RemoveStored(TObjectPtr<UItemInstance>& AssociatedInstance)
{
	UUIEquipSlotBase::RemoveStored(AssociatedInstance);

	PlayerEquipmentSubsystem->PlayerEquipmentDispatches.StorageRemoved.Broadcast(CollectableStorageInstance);
	CollectableStorageInstance = nullptr;
	SlotData.bOccupied = false;
}