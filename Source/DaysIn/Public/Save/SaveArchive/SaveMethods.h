#pragma once

/*
      
      Defines global methods for creating save slots and 
      loading save slots from disk.

*/



//Component imports.
#include "Kismet/GameplayStatics.h"


//Engine imports.
#include "CoreMinimal.h"



namespace SaveMethod
{

    /*
          Creates an async save slot on the user's disk when 
          called.

          @param SaveClass: pointer to a save class instance to create
          a slot from.

          @param SlotName: a string that holds the name of the slot
          you wish to make.

          @param SlotIndex: index of the slot (Defaulted to 0).
    */
    void MakeSaveSlot(USaveGame* SaveClass, const FString& SlotName, uint32_t SlotIndex = 0);


    /*
         Loads game from a save slot given the slot name, and index,
         then returns the loaded save instance to the caller.

         @param SlotName: string literal to the save slot 
         name. 

         @param SlotIndex: index to the save slot, defaulted to
         zero.

         @return USaveGame: pointer to the loaded save instance 
         back to the caller.
    */
    USaveGame* LoadSave(const FString& SlotName,uint32_t SlotIndex = 0);   
}