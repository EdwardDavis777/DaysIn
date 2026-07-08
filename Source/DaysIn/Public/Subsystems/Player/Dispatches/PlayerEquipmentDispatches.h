#pragma once

/*

      Defines player equipment dispatches triggered at
      runtime. All dispatch signatures are defined inside of the 
      PlayerEquipmentSubsystem.

*/


//Engine imports.
#include "CoreMinimal.h"


//Forward declares.
class UCollectableStorageInstance;




/*
      Dispatches when the player collects an external storage container. Such as a 
      backpack etc.

      @param AddedStorage: pointer to the storage that was 
      collected by the player.
*/
DECLARE_MULTICAST_DELEGATE_OneParam(FStorageAddedSignature, UCollectableStorageInstance* AddedStorage);



/*
     Dispatches when the player removes a collected external storage container. Such as a 
     backpack etc.

     @param RemovedStorage: pointer to the storage that was removed
     by the player.
*/
DECLARE_MULTICAST_DELEGATE_OneParam(FStorageRemovedSignature, UCollectableStorageInstance* RemovedStorage);




struct FPlayerEquipmentDelegates
{
    FStorageAddedSignature StorageAdded;
    FStorageRemovedSignature StorageRemoved;
};


