#pragma once

/*
      Defines global methods for spawning item objects
      into the world at run-time.
*/

//Config imports.
#include "Configs/ItemSpawnerConfigs.h"

 
//Engine imports.
#include "CoreMinimal.h"
 


//Forward declares.
class AItemBase;
class UItemInstance;
struct FSPKGSubInstance;




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


    /*
        Spawns an item through a given sub instances package struct,
        and returns a pointer to the spawned item to the caller.


        @param InnerPackage: reference to the inner package assocaited
        with the item you wish to spawn.

        @param WorldContext: pointer to the current world
        context.
    */
    AItemBase* SpawnInnerItem(const FSPKGSubInstance& InnerPackage, UWorld* WorldContext);
}