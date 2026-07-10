//Engine imports.
#include "UI/Storages/Abstracts/UICollectableStorageInventory.h"

//Component imports.
#include "Components/CanvasPanel.h"


//Other imports. 
#include "PlayerStorage/Abstracts/CollectableStorageInstance.h"

 
//Custom component imports.
#include "UI/Storages/Components/StorageUIInventoryComponent.h"
#include "CustomClasses/Components/Factory/NativeUITemplate.h"


//Utility imports.
#include "SubsystemUtilitys/SubsystemUtility.h"

//Subsystem imports.
#include "Subsystems/Systems/Inventory/StorageInventorySubsystem.h"
#include "Subsystems/Player/PlayerUISubsystem.h"



void UUICollectableStorageInventory::NativeConstruct()
{
	Super::NativeConstruct();

	StorageUIComponent = NativeUITemplate::CreateDefaultUIComponent<UStorageUIInventoryComponent>(GetWorld(), this);
	StorageInventorySubsystem = SubUtility::FindSub<UStorageInventorySubsystem>(GetWorld());
	BindDelegates();
}

void UUICollectableStorageInventory::InitializeGrid(int32 X, int32 Y, UObject* OwnerObject)
{
	Super::InitializeGrid(X, Y, OwnerObject);
	StorageInstance = FindOwner<UCollectableStorageInstance>();
}

void UUICollectableStorageInventory::BindDelegates()
{
	if (!StorageInventorySubsystem) return;
	StorageInventorySubsystem->StorageDispatches.ItemAddedEvent.AddUObject(this, &UUICollectableStorageInventory::AddItemEvent);
}



/*
                                      Event functions.
*/


void UUICollectableStorageInventory::AddItemEvent(UObject* StorageObject, UObject* AddedInstance, const FIntPoint& Position)
{
	if (!StorageObject || !AddedInstance || !StorageUIComponent) return;
	StorageUIComponent->HandleAddEvent(StorageObject, AddedInstance, Position, StorageInstance);
}



void UUICollectableStorageInventory::HookDragOverEvent(const FGeometry& InGeometry, const FDragDropEvent& InDragEvent, UDragDropOperation* InOperation)
{
	if (!StorageUIComponent) return;

	UUIGridInventoryBase::HookDragOverEvent(InGeometry, InDragEvent, InOperation);
	StorageUIComponent->HandleDragOver(InOperation, StorageInstance, Data.StoredDragWidgets,MouseGridPosition);
}

void UUICollectableStorageInventory::HookDragLeaveEvent(const FDragDropEvent& InDragEvent, UDragDropOperation* InOperation)
{
	if (!StorageUIComponent) return;
	StorageUIComponent->HandleDragLeave(InOperation);
}



bool UUICollectableStorageInventory::StoreDropped(UItemInstance* ItemInstance, const FIntPoint& Position)
{
	if (!ItemInstance || !StorageUIComponent || !PlayerUISubsystem) return false;
	
	if (StorageUIComponent->HandleDropped(ItemInstance, StorageInstance, MouseGridPosition))
	{
		return true;
	}
	
	PlayerUISubsystem->PlayerUISubsystemDispatches.ForceSpawnActor.Broadcast(ItemInstance); 
	return false;
}



void UUICollectableStorageInventory::RemoveStored(TObjectPtr<UItemInstance>& AssocaitedInstance)
{
	if (!AssocaitedInstance || !StorageUIComponent || !StorageInstance) return;
	StorageUIComponent->HandleRemove(Data.StoredDragWidgets, AssocaitedInstance, StorageInstance);
}