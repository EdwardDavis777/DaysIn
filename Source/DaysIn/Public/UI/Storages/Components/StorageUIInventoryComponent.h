#pragma once

/*
 
      Defines controller behavior for all collectable storage 
	  inventorys.

*/


//Engine imports. 
#include "CoreMinimal.h"
#include "CustomClasses/Components/NativeUIComponent.h" 
#include "StorageUIInventoryComponent.generated.h"


//Forward declares.
class UUICollectableStorageInventory;
class UCollectableStorageInstance;
class UItemInstance;
class UUIDraggableBase;
class UCanvasPanel;
class UDragDropOperation;
class UItemInstance;


UCLASS()
class DAYSIN_API UStorageUIInventoryComponent : public UNativeUIComponent
{
	GENERATED_BODY() 

public:
	virtual void Initialize(UWorld* WorldContext, UUserWidget* OwnerWidget) override;


	/*
	                            Inventory event functions.
	*/ 

	/*
	     Handles constructing widgets that could not be constructed during a 
		 storage event.

		 @param StorageCache: map of all items that need to have their widgets
		 constructed.
	*/
	void HandleRefresh(TMap<TObjectPtr<UItemInstance>, FIntPoint>& StorageCache);


	/*
	    Checks if the passed storage object from a store event, is equal to the owner storage instance; if they 
		are equal, this function will call a store function on the storage instance, and add the added instance
		icon to this inventory.

		@param StorageObject: pointer from a store dispatch event that holds the 
		invoked storage object from the event.

		@param AddedInstance: pointer to the item instance that is being
		added.

		@param Position: reference to the 2D position the instance is being stored
		at.

		@param StorageInstance: pointer to the storage instance
		that owns the inventory.
	*/
	void HandleAddEvent(UObject* StorageObject, UObject* AddedInstance, const FIntPoint& Position, UCollectableStorageInstance* StorageInstance);



	/*
	     Handles the drag over event, will check if the item at its current mouse position
		 can be stored inside of the dragged over inventory instance. Will change the 
		 color of the InOperation payload widget to a can place color if possible.

		 @param InOperation: pointer to the current drag drop 
		 operation.

		 @param StorageInstance: pointer to the current assocaited
		 storage instance.

		 @param MousePosition: reference to the current mouse 
		 position in grid space.
	*/
	void HandleDragOver(UDragDropOperation* InOperation, UCollectableStorageInstance* StorageInstance, TMap<TObjectPtr<UItemInstance>, TObjectPtr<UUIDraggableBase>>& StoredWidgets,const FIntPoint& MousePosition);


	/*
	     Handles drag leave events; simply resetting the dragging icon to its 
		 class defaults once the drag event is over.

		 @param InOperation: pointer to the current drag and 
		 drop operation.
	*/
	void HandleDragLeave(UDragDropOperation* InOperation);

	/*
	      Checks if the passed instance can be stored inside of the collectable
		  storage instance.

		  @param Instance: pointer to the dropped item
		  instance. 

		  @param StorageInstance: pointer to the current storage instance
		  assocaited with this inventory.

		  @param DroppedGridPosition: reference to the current mouse grid
		  position during the drop event.

		  @return TRUE/FALSE: true if the instance can be stored in the grid 
		  position, false if the instance cannot be stored in the dropped grid
		  position.
	*/
 	bool HandleDropped(UItemInstance* Instance, UCollectableStorageInstance* StorageInstance, const FIntPoint& DroppedGridPosition);


	/*
	    Clears the dropped instance from the stored widgets cache, and removes the 
		assocaited widget instance from this inventorys group panel.

		@param StoredWidgets: map to all stored widgets, and assocaited
		item instances.

		@param AssocaitedInstance: pointer to the removed
		instance.
	*/
	void HandleRemove(TMap<TObjectPtr<UItemInstance>, TObjectPtr<UUIDraggableBase>>& StoredWidgets, TObjectPtr<UItemInstance>& AssocaitedItem,UCollectableStorageInstance* StorageInstance);

private:   
	
	/*
	                                Components.
	*/
	UPROPERTY()
	TObjectPtr<UUICollectableStorageInventory> StorageInventory;
};