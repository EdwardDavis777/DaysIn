//Engine imports.
#include "UI/Storages/Components/StorageUIInventoryComponent.h"


//Component imports.
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"


//Widget imports.
#include "UI/Storages/Abstracts/UICollectableStorageInventory.h"
#include "UI/Interactables/Abstracts/UIDraggableBase.h" 

 
//Other imports.
#include "PlayerStorage/Abstracts/CollectableStorageInstance.h"
#include "PlayerStorage/Components/StorageInventoryComponent.h"

#include "UI/Interactables/Abstracts/GlobalEvents/DraggableColorMethods/ColorMethods.h"
#include "UI/Interactables/Abstracts/GlobalEvents/DraggableTemplates/DraggableTemplates.h"
#include "Items/Abstracts/ItemInstance.h"



void UStorageUIInventoryComponent::Initialize(UWorld* WorldContext, UUserWidget* OwnerWidget)
{
	Super::Initialize(WorldContext, OwnerWidget);
	StorageInventory = FindOwner<UUICollectableStorageInventory>();
}




/*
							         Inventory event functions.
*/
 
void UStorageUIInventoryComponent::HandleRefresh(TMap<TObjectPtr<UItemInstance>, FIntPoint>& StorageCache)
{
	if (StorageCache.IsEmpty() || !StorageInventory) return;
    
	for (auto& Cache : StorageCache)
	{
		if (!Cache.Key.Get()) continue;
		StorageInventory->StoreItem(Cache.Key, Cache.Value);
	}
}


void UStorageUIInventoryComponent::HandleAddEvent(UObject* StorageObject, UObject* AddedInstance, const FIntPoint& Position, UCollectableStorageInstance* StorageInstance)
{
	if (!StorageInstance || !StorageInventory) return;

	auto* EventOwner = Cast<UCollectableStorageInstance>(StorageObject);
	if (!EventOwner || EventOwner != StorageInstance) return;

	auto* ItemInstance = Cast<UItemInstance>(AddedInstance);
	if (!ItemInstance) return;

	StorageInventory->StoreItem(ItemInstance, Position);
}



void UStorageUIInventoryComponent::HandleDragOver(UDragDropOperation* InOperation, UCollectableStorageInstance* StorageInstance, TMap<TObjectPtr<UItemInstance>, TObjectPtr<UUIDraggableBase>>& StoredWidgets,const FIntPoint& MousePosition)
{
	if (!InOperation || !InOperation->Payload || !StorageInstance || !StorageInventory) return;

	auto* DraggingWidget = DraggableTemplate::GetPayload<UUIDraggableBase>(InOperation);
	UItemInstance* DragInst = DraggableTemplate::GetPayloadInstance<UUIDraggableBase>(InOperation);
	if (!DraggingWidget || !DragInst) return;
   
	if (StorageInstance->GetInventoryComponent()->bCanStore(DragInst, MousePosition))
	{
		ColorMethod::SetCanPlaceColor(DraggingWidget);
	}
	else
	{
		ColorMethod::SetCannotPlaceColor(DraggingWidget);
	}
}



void UStorageUIInventoryComponent::HandleDragLeave(UDragDropOperation* InOperation)
{
	if (!InOperation || !InOperation->Payload) return;

	auto* DraggingWidget = DraggableTemplate::GetPayload<UUIDraggableBase>(InOperation);
	if (!DraggingWidget) return;

	ColorMethod::SetDefaultColor(DraggingWidget);
}
 



bool UStorageUIInventoryComponent::HandleDropped(UItemInstance* Instance, UCollectableStorageInstance* StorageInstance, const FIntPoint& DroppedGridPosition)
{
	if (!Instance || !StorageInstance) return false;
	return StorageInstance->GetInventoryComponent()->bCheckAndStore(Instance, DroppedGridPosition);
}




void UStorageUIInventoryComponent::HandleRemove(TMap<TObjectPtr<UItemInstance>,TObjectPtr<UUIDraggableBase>>& StoredWidgets, TObjectPtr<UItemInstance>& AssocaitedInstance, UCollectableStorageInstance* StorageInstance)
{
	if (StoredWidgets.IsEmpty() || !AssocaitedInstance || !StorageInstance) return;

	if (auto* StoredWidget = StoredWidgets.Find(AssocaitedInstance))
	{
		StoredWidget->Get()->RemoveFromParent();
		StoredWidgets.Remove(AssocaitedInstance);
		StorageInstance->GetInventoryComponent()->RemoveItem(AssocaitedInstance);
	}
}