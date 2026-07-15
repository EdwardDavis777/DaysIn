#pragma once

/*

      Defines inventory dispatches for the StorageInventorySubsystem;
      all signatures are defined inside of that subsystem.

*/


//Engine imports.
#include "CoreMinimal.h"


/*
     Dispatched when an item is added to some players storage 
     object.

     @param StorageInstnace: pointer to the current storage item that 
     is being used.

     @param AddedInstance: pointer to the instance that was 
     actually stored.

     @param Position: reference to the 2D position the instance
     was added to.
*/
DECLARE_MULTICAST_DELEGATE_ThreeParams(FItemAddedEventSignature, UObject* StorageInstance, UObject* AddedInstance, const FIntPoint& Position);



/*
    Dispatched when an item is removed from some players storage
    object.

    @param StorageInstance: pointer to some storage
    instance.

    @param RemovedInstance: pointer to some
    removed object instance.
*/
DECLARE_MULTICAST_DELEGATE_TwoParams(FItemRemovedEventSignature, UObject* StorageInstance, UObject* RemovedInstnace);




struct FStorageInventoryDelegates
{
    FItemAddedEventSignature ItemAddedEvent;
    FItemRemovedEventSignature ItemRemovedEvent;
};