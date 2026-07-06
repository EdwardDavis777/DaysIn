//Engine imports.
#include "PlayerStorage/Components/StorageInventoryComponent.h"



//Other imports.
#include "PlayerStorage/Abstracts/CollectableStorageInstance.h"
#include "Items/Abstracts/ItemBase.h"

#include "PlayerStorage/Components/CollectableStorageUIComponent.h"
#include "UI/Storages/Abstracts/UICollectableStorageInventory.h"




void UStorageInventoryComponent::Initialize(UWorld* WorldContext, UObject* OwnerObject)
{
	Super::Initialize(WorldContext, OwnerObject);
	
	if (CollectableStorageInstance = GetOwner<UCollectableStorageInstance>())
	{
		Columns = CollectableStorageInstance->GetSize().X;
		Rows = CollectableStorageInstance->GetSize().Y;
		StoredItems.SetNum(Columns * Rows);
	}
}





/*
                                 Placement functions. 
*/

void UStorageInventoryComponent::AddItem(UItemInstance* Instance, const int32& Origin)
{
	if (!Instance) return;

	const FIntPoint ItemSize = Instance->GetItemSize();
	const FIntPoint Tile = IndexToTile(Origin);

	for (int32 xPos{ Tile.X }; xPos < Tile.X + ItemSize.X; xPos++)
	{
		for (int32 yPos{ Tile.Y }; yPos < Tile.Y + ItemSize.Y; yPos++)
		{
			StoredItems[TileToIndex(FIntPoint(xPos, yPos))] = Instance;
		}
	}
	CollectableStorageInstance->GetStorageUIComponent()->GetInventoryWidget()->StoreItem(Instance, Tile);
}



/*
                                     Conditionals.
*/

bool UStorageInventoryComponent::bCanStore(AItemBase* Item)
{
	if (!Item) return false;

	for (int32 i{}; i <= StoredItems.Num(); i++)
	{
		if (bCanFit(Item->Instance(), i))
		{
			AddItem(Item->Instance(), i);
			Item->Pickup();
			return true;
		}
	}
	return false;
}


bool UStorageInventoryComponent::bCanFit(UItemInstance* Instance, int32 Origin)
{
	if (!Instance) return false;
	
	const FIntPoint ItemSize = Instance->GetItemSize();
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