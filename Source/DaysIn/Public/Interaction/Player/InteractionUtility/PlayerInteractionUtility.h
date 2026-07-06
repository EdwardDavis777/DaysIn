#pragma once

/*
      Defines helper functions for player interaction
      events.
*/


//Engine imports.
#include "CoreMinimal.h"



//Forward declares.
class AItemBase;
class ASurvivor; 
class UUIPlayerEquipmentMain;
class UCollectableStorageInstance;




namespace Interact
{

    /*
         Performs a distance check to find the nearest item to the player character from 
         the overlapped items, then returns a pointer to the nearest item to the caller.

         @param OverlappeItems: array of all overlapped items.

         @param Player: pointer to the current player
         character.

         @return AItemBase: pointer to the nearst item in the overlapped
         items array.
    */
    AItemBase* FindNearest(const TArray<TObjectPtr<AItemBase>>& OverlappedItems, TObjectPtr<ASurvivor> Player);






    /*
         Checks if any equipment slots inside of the players static UI equipment
         widget can store the associated item. If it can it will call its store method
         and return true.

         @param EquipmentMain: pointer to the players UIEquipmentMain widget 
         instance.

         @param Item: pointer to the current item object the player
         is trying to pickup.

         @return TRUE/FALSE: true if a slot can store it, false
         if no slot can store it.
    */
    bool bStoreInSlot(UUIPlayerEquipmentMain* EquipmentMain, AItemBase* Item);



    /*
          Parses all external player storages and stores the item inside of the first
          storage instance that can hold the item.

          @param Storages: array of all external player 
          storages.

          @param Item: pointer to the item you wish to
          store.
    */
    void StoreInExternalStorage(const TArray<TObjectPtr<UCollectableStorageInstance>>& Storages,AItemBase* Item);
}