#pragma once

/*
      Defines player related dispatch signatures for global
      event triggers.
*/


//Engine imports.
#include "CoreMinimal.h"


//Forward declares.
class AItemBase;


/*

     Dispatched when the player character is in the vicinity of an item
     that can be picked up.

     @param Item: pointer to the current item in the vicinity 
     of the player character.

*/
DECLARE_MULTICAST_DELEGATE_OneParam(FItemInVicinitySignature, AItemBase* Item);


/*
    Dispatched when the player character hits their interaction key and trys to 
    pick up and item. The dispatch itself does not carry the item, note the dispatch
    is meant to be binded to an overlap function that already is tracking 
    overlapped items or something.
*/
DECLARE_MULTICAST_DELEGATE(FTryPickupItemSignature);


/*
    Dispatched when an item is picked up by the player character, will carry the pointer
    to all listeners.

    @param Item: pointer to the item that was picked up by the 
    player character.
*/
DECLARE_MULTICAST_DELEGATE_OneParam(FPickupItemSignature, AItemBase* Item);




struct FPlayerSubsystemDelegates
{
    FItemInVicinitySignature ItemInVicinity;
    FTryPickupItemSignature TryPickupItem;
    FPickupItemSignature PickupItem;
};