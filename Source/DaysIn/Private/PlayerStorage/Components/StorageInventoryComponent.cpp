//Engine imports.
#include "PlayerStorage/Components/StorageInventoryComponent.h"



//Other imports.
#include "PlayerStorage/Abstracts/CollectableStorageInstance.h" 
#include "Items/Abstracts/ItemBase.h"

#include "PlayerStorage/Components/CollectableStorageUIComponent.h"
#include "UI/Storages/Abstracts/UICollectableStorageInventory.h"



//Utility imports.
#include  "SubsystemUtilitys/SubsystemUtility.h"

//Subsystem imports.
#include "Subsystems/Systems/Inventory/StorageInventorySubsystem.h"




void UStorageInventoryComponent::Initialize(UWorld* WorldContext, UObject* OwnerObject)
{
	Super::Initialize(WorldContext, OwnerObject);
	
	if (CollectableStorageInstance = GetOwner<UCollectableStorageInstance>())
	{
		Columns = CollectableStorageInstance->GetSize().X;
		Rows = CollectableStorageInstance->GetSize().Y;
		StoredItems.SetNum(Columns * Rows);
		StorageInventorySubsystem = SubUtility::FindSub<UStorageInventorySubsystem>(WorldContext);
	}
}





/* 
                                  Mutator functions. 
*/ 

void UStorageInventoryComponent::AddItem(UItemInstance* Instance, const int32& Origin)
{
	if (!Instance || !StorageInventorySubsystem) return;

	const FIntPoint ItemSize = Instance->GetDynamicUISize();
	const FIntPoint Tile = IndexToTile(Origin);

	for (int32 xPos{ Tile.X }; xPos < Tile.X + ItemSize.X; xPos++)
	{
		for (int32 yPos{ Tile.Y }; yPos < Tile.Y + ItemSize.Y; yPos++)
		{
			StoredItems[TileToIndex(FIntPoint(xPos, yPos))] = Instance;
		}
	}
	StorageCache.Emplace(Instance, Tile);


	//Triggering global storage event.
	StorageInventorySubsystem->StorageDispatches.ItemAddedEvent.Broadcast(
	CollectableStorageInstance, Instance, Tile);
}

void UStorageInventoryComponent::RemoveItem(UItemInstance* Instance)
{
	if (!Instance || StoredItems.IsEmpty()) return;

	if (StoredItems.Contains(Instance))
	{
		for (int32 i{}; i < StoredItems.Num(); i++)
		{
			if (StoredItems[i] == Instance) { StoredItems[i] = nullptr; }
		}
		StorageCache.Remove(Instance);


		//Triggering global removal event.
		StorageInventorySubsystem->StorageDispatches.ItemRemovedEvent.Broadcast(
		CollectableStorageInstance, Instance);
	}
}


 



/*
								   Mutator conditions.
*/

bool UStorageInventoryComponent::bCheckAndStore(UItemInstance* Instance, FIntPoint Position)
{
	if (!Instance) return false; 

	int32 Index = TileToIndex(Position);
	if (bCanStore(Instance, Index))
	{
		AddItem(Instance, Index);
		return true;
	}
	return false;
}

bool UStorageInventoryComponent::bCheckAndStore(AItemBase* Item, const FIntPoint& position)
{ 
	if (!Item) return false;

	int32 Index = TileToIndex(position);
	if (bCanStore(Item->Instance(), Index))
	{
		AddItem(Item->Instance(), Index);
		Item->Pickup();
		return true;
	}
	return false;
}


bool UStorageInventoryComponent::bCheckAndStore(AItemBase* Item)
{
	if (!Item) return false;
	 
	for (int32 i{}; i < StoredItems.Num(); i++)
	{
		if (bCanStore(Item->Instance(), i))
		{
			AddItem(Item->Instance(), i);
			Item->Pickup();
			return true;
		}
	}
	return false;
}



/*
									 Conditionals.
*/

bool UStorageInventoryComponent::bCanStore(UItemInstance* Instance, int32 Origin)
{
	if (!Instance) return false;
	
	const FIntPoint ItemSize = Instance->GetDynamicUISize();
	const FIntPoint Tile = IndexToTile(Origin);

	for (int32 xPos{ Tile.X }; xPos < Tile.X + ItemSize.X; xPos++)
	{
		for (int32 yPos{ Tile.Y }; yPos < Tile.Y + ItemSize.Y; yPos++)
		{
			const int32 Index{ TileToIndex(FIntPoint(xPos,yPos)) };
			if (bIsValidTile(FIntPoint(xPos, yPos)))
			{
				if (!bIsValidIndex(Index)) return false;
			}
			else { return false; }
		}
	}
	return true;
}

bool UStorageInventoryComponent::bCanStore(UItemInstance* Instance, const FIntPoint& Position)
{
	if (!Instance) return false;

	const FIntPoint ItemSize = Instance->GetDynamicUISize();

	for (int32 xPos{ Position.X }; xPos < Position.X + ItemSize.X; xPos++)
	{
		for (int32 yPos{ Position.Y }; yPos < Position.Y + ItemSize.Y; yPos++)
		{
			const int32 Index{ TileToIndex(FIntPoint(xPos,yPos)) };
			if (bIsValidTile(FIntPoint(xPos, yPos)))
			{
				if (!bIsValidIndex(Index)) return false;
			}
			else { return false; }
		}
	}
	return true;
}





bool UStorageInventoryComponent::bIsValidIndex(const int32& Index) const
{
	if (StoredItems.IsValidIndex(Index) && !StoredItems[Index]) return true;
	return false;
}


bool UStorageInventoryComponent::bIsValidTile(const FIntPoint& Tile) const
{
	if (Tile.X >= 0 && Tile.Y >= 0 &&
	Tile.X < Columns && Tile.Y < Rows) return true;

	return false;
}


/*
                                     Accessors.
*/

TMap<TObjectPtr<UItemInstance>, FIntPoint>& UStorageInventoryComponent::GetStorageCache()
{
	return StorageCache;
}