#pragma once

/*

      Defines inventory gameplay functions/ functions that execute
	  behavior for the inventorys that belong to collectable storages.

*/ 

  

//Engine imports.
#include "CoreMinimal.h"
#include "CustomClasses/Components/GameplayComponent.h"
#include "StorageInventoryComponent.generated.h"



//Forward declares. 
class UCollectableStorageInstance;
class UStorageInventorySubsystem;
class AItemBase;
class UItemInstance;

  

UCLASS()
class DAYSIN_API UStorageInventoryComponent : public UGameplayComponent
{
	GENERATED_BODY()

public:
	virtual void Initialize(UWorld* WorldContext, UObject* OwnerObject) override;
	

	 
	/*
	                              Mutators.
	*/

	/*
	     Adds an item at the given origin index, note this function
		 does not provide any safe checks, it will simply force
		 and item into the inventory, so ensure that you provide
		 the correct checks, such as calling bCanStore first.

		 @param Instance: pointer to the current item instance
		 you wish to add.

		 @param Origin: reference to the start index you wish 
		 to add the instance from.
	*/
	void AddItem(UItemInstance* Instance,const int32& Origin);


	/*
		 Removes all instances found in this inventory that match the passed
		 instance type by the caller.

		 @param Instance: pointer to the item instance you wish to
		 remove.
	*/
	void RemoveItem(UItemInstance* Instance);



	/*
	                            Mutator conditions.
	*/


	/*
	    Checks if an instance can be stored given a 2D mouse position,
	    the function will convert the 2D position to an index, then
	    perform storage checks. If all checks succeed, then the item will
	    be stored at the given position.

	    @param Instance: pointer to the item instance you wish
	    to store.

	    @param Position: Copy to a 2D position; Note a copy is needed
	    as it will mutate the state.

	    @return TRUE/FALSE: true if the item was stored, false if the item
	    cannot be stored for some reason.
    */
	bool bCheckAndStore(UItemInstance* Instance, FIntPoint Position);

	/*
	    Checks if a raw item poiinter can be stored given a 2D mouse position,
	    the function will convert the 2D position to an index, then
	    perform storage checks. If all checks succeed, then the item will
	    be stored at the given position.

	    @param Item: pointer to a raw item you wish
	    to store.

	    @param Position: Copy to a 2D position; Note a copy is needed
	    as it will mutate the state.

	    @return TRUE/FALSE: true if the item was stored, false if the item
	    cannot be stored for some reason.
	*/
	bool bCheckAndStore(AItemBase* Item, const FIntPoint& position);

	/*
		Checks if the passed item can be stored inside of this
		inventory component.

		@param Item: pointer to the item you wish to
		store.

		@return TRUE/FALSE: true if the item gets stored, false
		if the item cannot be stored.
	*/
	bool bCheckAndStore(AItemBase* Item);



	/*
								   Conditionals.
    */

	/*
	     Checks if the given instance can fit inside of the inventory
		 array cache given a starting index.

		 @param Instance: pointer to the instance you wish 
		 to store.

		 @param Origin: starting index in the inventory 
		 array.
         
		 @return TRUE/FALSE: true if the instance can fit, false
		 if the instance cannot.
	*/
	bool bCanStore(UItemInstance* Instance, int32 Origin);


	/*
	     Checks if the given instance can fit inside of the inventory
		 array cache given a 2D position.

		 @param Instance: pointer to the instance you wish 
		 to store.

		 @param Position: 2D position you wish to use as the starting
		 point.
         
		 @return TRUE/FALSE: true if the instance can fit, false
		 if the instance cannot.
	*/
	bool bCanStore(UItemInstance* Instance, const FIntPoint& Position);


	/*
	     Checks if the current index is occupied (valid meaning 
		 not nullptr), will return true if the index returns a valid
		 pointer, and false if the index is assocaited with a nullptr.
		 Also checks if the index is within the bounds of the stored items
		 reserved allocated space.

		 @param Index: reference to the current index you wish 
		 to check.

		 @return TRUE/FLASE: true if the index is valid, false
		 if the index is nullptr or out of bounds.
	*/
	bool bIsValidIndex(const int32& Index) const;



	/*
	     Checks if the passed tile cord is valid, or invalid
		 meaning inside the inventory bounds, returns true if the tile
		 is valid, false if the tile is invalid for some reason.

		 @param Tile: reference to the tile you wish to 
		 check.

		 @return TRUE/FLASE: true if the tile is valid, false if the 
		 tile is invalid.
	*/
	bool bIsValidTile(const FIntPoint& Tile) const;



	/*
	                                 Math functions.
	*/
	


	/*
	     Converts an array index into a 2D cord and returns the 
		 cord back to the caller.

		 @param Index: reference to the current index you wish
		 to convert from.

		 @return FIntPoint(): the index converted to a coord
		 back to the caller.
	*/
	FORCEINLINE FIntPoint IndexToTile(const int32& Index) const
	{
		return FIntPoint(Index % Columns, Index / Columns);
	}



	/*
	     Converts a 2D cord into an index and returns the index to 
		 the caller.

		 @param Tile: reference to the tile you wish to convert
		 to an index.

		 @return int32(): current index of the passed
		 tile.
	*/
	FORCEINLINE int32 TileToIndex(const FIntPoint& Tile) const
	{
		return Tile.X + Tile.Y * Columns;
	}

	
	/*
	                                  Accessors.
	*/
	TMap<TObjectPtr<UItemInstance>, FIntPoint>& GetStorageCache();
private:

	
	/*
	                                  Components.  
	*/
	UPROPERTY()
	TObjectPtr<UCollectableStorageInstance> CollectableStorageInstance;

	UPROPERTY()
	TObjectPtr<UStorageInventorySubsystem> StorageInventorySubsystem;
   

    /*
	                               Cache components.
	*/
	UPROPERTY()
	TArray<TObjectPtr<UItemInstance>> StoredItems;

	UPROPERTY()
	TMap<TObjectPtr<UItemInstance>, FIntPoint> StorageCache;


	UPROPERTY()
	int32 Columns = int32();

	UPROPERTY()
	int32 Rows = int32();
};