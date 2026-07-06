//Engine imports.
#include "Interaction/Player/InteractionUtility/PlayerInteractionUtility.h"

//Component imports.
#include "Components/CanvasPanel.h"


//Other imports.
#include "Items/Abstracts/ItemBase.h"
#include "PlayerStorage/Abstracts/CollectableStorageInstance.h"
#include "PlayerStorage/Components/StorageInventoryComponent.h"
#include "Characters/Player/Survivor.h"

#include "UI/Player/UIPlayerEquipmentMain.h"
#include "UI/Player/UIEquipSlotBase.h" 



namespace Interact
{ 
	AItemBase* FindNearest(const TArray<TObjectPtr<AItemBase>>& OverlappedItems, TObjectPtr<ASurvivor> Player)
	{
		if (OverlappedItems.IsEmpty() || !Player) return nullptr;

		float NearestDist = TNumericLimits<float>::Max();
		AItemBase* NearestItem = nullptr;
		FVector PlayerLocation = Player->GetActorLocation();

		for (const auto& Item : OverlappedItems)
		{
			if (!Item) continue;

			float Dist = FVector::Dist(PlayerLocation, Item->GetActorLocation());
			if (Dist < NearestDist)
			{
				NearestDist = Dist;
				NearestItem = Item;
			}
		}
		return NearestItem;
	}

	bool bStoreInSlot(UUIPlayerEquipmentMain* EquipmentMain, AItemBase* Item)
	{
		if (!EquipmentMain || !Item) return false;

		const TArray<UWidget*> Children = EquipmentMain->GetGroupPanel()->GetAllChildren();
		for (const auto& Child : Children)
		{
			if (!Child) continue;
			
			if (auto* Slot = Cast<UUIEquipSlotBase>(Child))
			{
				if (Slot->GetEquipTag() == Item->GetEquipTag() && !Slot->IsOccupied())
				{
					Slot->StoreItem(Item);
					return true;
				}
			}
		}
		return false;
	}

	void StoreInExternalStorage(const TArray<TObjectPtr<UCollectableStorageInstance>>& Storages, AItemBase* Item)
	{
		if (Storages.IsEmpty() || !Item) return;

		for (auto& Storage : Storages)
		{
			if (Storage || Storage->GetInventoryComponent())
			{
				if (Storage->GetInventoryComponent()->bCanStore(Item)) { return; }
			}
		}
	}
}