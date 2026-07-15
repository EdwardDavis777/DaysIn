//Engine imports.
#include "Save/Abstracts/SavePlayerEquipment.h"

//Component imports.
#include "Components/CanvasPanel.h"


 
//Other imports.
#include "Items/Abstracts/ItemInstance.h"
#include "Items/Abstracts/ItemBase.h"
#include "UI/Player/UIPlayerEquipmentMain.h"
#include "UI/Player/UIEquipSlotBase.h" 



//Utility imports. 
#include "SubsystemUtilitys/SubsystemUtility.h"

//Subsystem imports.
#include "Subsystems/Player/PlayerUISubsystem.h"




USavePlayerEquipment::USavePlayerEquipment()
{
	SaveName = "EquipmentSave";
}



 
/*
							   Forced event functions.
*/

void USavePlayerEquipment::ProxyInstance(UItemInstance* Instance)
{
	if (!Instance) return;
	
	if (!ProxyCache.Contains(Instance)) 
	{ 
		auto& Package = ProxyCache.FindOrAdd(Instance);
		Package.ItemClass = Instance->GetStaticItemData()->ItemProperties.ItemClass;
	}
}

void USavePlayerEquipment::PostLoadSave(UWorld* WorldContext)
{
	if (!WorldContext) return;
	
	PlayerUISubsystem = SubUtility::FindSub<UPlayerUISubsystem>(WorldContext);
	LoadToSlots();
}




/*
							     Load event functions.
*/

void USavePlayerEquipment::LoadToSlots()
{
	if (LoadedAssets.IsEmpty() || !PlayerUISubsystem) return;

	TArray<UWidget*> Slots = PlayerUISubsystem->GetEquipmentMain()->GetGroupPanel()->GetAllChildren();	
	for (auto& Asset : LoadedAssets)
	{
		for (auto& Slot : Slots)
		{
			if (auto* EquipSlot = Cast<UUIEquipSlotBase>(Slot))
			{
				if (EquipSlot->GetEquipTag() == Asset->GetEquipTag())
				{
					auto* Instance = Asset->Instance();
					if (!Instance) continue;

					EquipSlot->StoreItem(Asset);
					Instance->PostOuterDeserialize();
				}
			}
		}
	}
	LoadedAssets.Empty();
}