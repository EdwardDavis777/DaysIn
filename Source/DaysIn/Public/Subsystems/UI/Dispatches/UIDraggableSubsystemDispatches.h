#pragma once

/*
    Defines dispatches for the UIDraggableSubsystem; all signatures
    are defined inside of the subsystem.
*/


//Engine imports.
#include "CoreMinimal.h"


//Forward declares.
class UItemInstance;



/*
     Dispatches to widgets that are currently storing a draggable widget instance 
     that it has been dragged out of their instance. The assocaited instance is 
     used for other listeners to compare against the instance. Avoids double event 
     dispatches.

     @param AssocaitedInstance: pointer to the item instance assocaited with 
     the dragged widget, and the current owner of the drag instance.
*/
DECLARE_MULTICAST_DELEGATE_OneParam(FDragEventTriggeredSignature, TObjectPtr<UItemInstance>& AssocaitedInstance); 




struct FDraggableDispatches
{
    FDragEventTriggeredSignature DragEventTriggered;
};