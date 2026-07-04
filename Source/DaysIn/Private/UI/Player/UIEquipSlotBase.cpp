//Engine imports.
#include "UI/Player/UIEquipSlotBase.h"

//Component imports.
#include "Components/Border.h"


//Other imports.
#include "Items/Abstracts/ItemInstance.h"
#include "Items/Abstracts/ItemBase.h" 


//Widget imports.
#include "UI/Items/Abstracts/UIItemIconBase.h"


//Custom component imports.
#include "UI/Player/Components/EquipSlotUIComponent.h"
#include "CustomClasses/Components/Factory/NativeUITemplate.h"


//Subsystem imports.
#include "Subsystems/Player/PlayerUISubsystem.h"




void UUIEquipSlotBase::NativeConstruct()
{
	Super::NativeConstruct();
	EquipSlotUIComponent = NativeUITemplate::CreateDefaultUIComponent<UEquipSlotUIComponent>(GetWorld(), this);

	if (MainBorder)
	{
		SlotColorData.DefaultBorderColor = MainBorder->GetBrushColor();
	}
}




/*
							         Virtual event functions.
*/

void UUIEquipSlotBase::StoreItem(AItemBase* Item)
{
	if (!Item) return;

	EquipSlotUIComponent->HandleStore(Item->Instance(), ItemIcon, SlotData.StoredItem);
	CacheExternalSourceWidget(SlotData.StoredItem, ItemIcon);
}


bool UUIEquipSlotBase::StoreDropped(UItemInstance* ItemInstance)
{
	if (!ItemInstance) return false;
	
	if(EquipSlotUIComponent->bCanStore(ItemInstance))
	{ 
     	EquipSlotUIComponent->HandleStore(ItemInstance, ItemIcon, SlotData.StoredItem);
	    EquipSlotUIComponent->ResetBorder(SlotColorData.DefaultBorderColor);
	    CacheExternalSourceWidget(SlotData.StoredItem, ItemIcon);
	   
	   return true;
	}
	else
	{
		PlayerUISubsystem->PlayerUISubsystemDispatches.ForceSpawnActor.Broadcast(ItemInstance);
	}
	return false;
}


void UUIEquipSlotBase::RemoveStored(TObjectPtr<UItemInstance>& AssocaitedInstance)
{
	Super::RemoveStored(AssocaitedInstance);
	EquipSlotUIComponent->HandleRemove(AssocaitedInstance,SlotData.StoredItem, ItemIcon);
}



/*
								    Virtual hook functions.
*/

void UUIEquipSlotBase::HookDragOverEvent(UDragDropOperation* InOperation)
{
	if (!InOperation) return;
	EquipSlotUIComponent->HandleHoverOver(InOperation, SlotColorData.CanPlaceColor);
}

void UUIEquipSlotBase::HookDragLeaveEvent()
{
	EquipSlotUIComponent->ResetBorder(SlotColorData.DefaultBorderColor);
}

void UUIEquipSlotBase::HookResetEvent()
{
	EquipSlotUIComponent->ResetBorder(SlotColorData.DefaultBorderColor);
}



/*
                                           Accessors.
*/

const EEquipTag UUIEquipSlotBase::GetEquipTag() const
{
	return EquipTag;
}

const bool& UUIEquipSlotBase::IsOccupied() const
{
	return SlotData.bOccupied;
}

UTextBlock* UUIEquipSlotBase::GetDescription() const
{
	return SlotDescription.Get();
}

UUIItemIconBase* UUIEquipSlotBase::GetIcon() const
{
	return ItemIcon.Get();
}