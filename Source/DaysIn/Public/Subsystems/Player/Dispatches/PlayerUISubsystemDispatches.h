#pragma once

/*
     Defines player UI dispatch signatures; all signatures in the struct 
     below are defined inside of the PlayerUISubsystem.
*/


//Engine imports.
#include "CoreMinimal.h"
 
//Forward declares.
class UItemInstance;


/*
     Dispatch to toggle the UIPlayerMain widget 
     instance to render/remove from render.
*/
DECLARE_MULTICAST_DELEGATE(FToggleUIMainSignature);


/*
    Dispatches to listeners when the players UI main is currently 
    in render/toggled visible.
*/
DECLARE_MULTICAST_DELEGATE(FUIMainInRenderSignature);

/*
    Dispatches listeners when the players UI main is currently 
    out of render/toggled collapsed.
*/
DECLARE_MULTICAST_DELEGATE(FUIMainOutRenderSignature);


/*
    Dispatches to the UI main widget to force spawn an 
    item through some passed instance.

    @param ItemInstance: pointer to an item instance you wish
    to spawn an actor from.
*/
DECLARE_MULTICAST_DELEGATE_OneParam(FForceSpawnActorSignature, UItemInstance* ItemInstance);



struct FPlayerUISubsystemDelegates
{
    FToggleUIMainSignature ToggleUIMain;
    FUIMainInRenderSignature UIMainInRender;
    FUIMainOutRenderSignature UIMainOutRender;
    FForceSpawnActorSignature ForceSpawnActor;
};