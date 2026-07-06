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
		SlotData.bOccupied = true;
		PlayerEquipmentSubsystem->AddStorage(CollectableStorageInstance);
		Item->Pickup();
	}
}

bool UUIStorageSlot::StoreDropped(UItemInstance* ItemInstance)
{
	if (UUIEquipSlotBase::StoreDropped(ItemInstance))
	{
		CollectableStorageInstance = FindAssocaitedInstance<UCollectableStorageInstance>();
		CollectableStorageInstance->GetStorageUIComponent()->RebuildInRegion();
		PlayerEquipmentSubsystem->AddStorage(CollectableStorageInstance);
		SlotData.bOccupied = true;
		return true;
	}
	return false;
}

void UUIStorageSlot::RemoveStored(TObjectPtr<UItemInstance>& AssocaitedInstance)
{
	UUIEquipSlotBase::RemoveStored(AssocaitedInstance);

	PlayerEquipmentSubsystem->RemoveStorage(CollectableStorageInstance);
	CollectableStorageInstance->GetStorageUIComponent()->ClearInventory();
	CollectableStorageInstance = nullptr;
	SlotData.bOccupied = false;
}