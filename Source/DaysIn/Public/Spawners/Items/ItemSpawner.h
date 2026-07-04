#pragma once

/*
      Defines global methods for spawning item objects
      into the world at run-time.
*/


//Engine imports.
#include "CoreMinimal.h"
 
//Forward declares.
class AItemBase;
class UItemInstance;


namespace ItemSpawner
{
    /*
         Spawns an item at the world origin given an item class 
         reference and returns a pointer of the spawned item 
         back to the caller.

         @param ItemClass: refrence to the item class you wish 
         to spawn an item from.

         @param WorldContext: pointer to the current world
         context.

         @return AItemBase: pointer to the spawned item.
    */
    AItemBase* SpawnItemLazy(const TSubclassOf<AItemBase>& ItemClass,UWorld* WorldContext);
}