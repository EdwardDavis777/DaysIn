#pragma once

/*

       Defines dispatches for item runtime events. All dispatch
       signatures are defined inside of the item event subsystem.

*/


//Engine imports.
#include "CoreMinimal.h"


//Forward declares.
class UItemInstance;


/*
     Dispatched whenever an item is dropped inside of the world
     from a user interface or some other way.

     @param DroppedInstance: pointer to the dropped items
     new/re-used instance.
*/
DECLARE_MULTICAST_DELEGATE_OneParam(FItemDroppedSignature, UItemInstance* DroppedInstance);



struct FItemEventSubsystemDelegates
{
    FItemDroppedSignature ItemDropped;
};

