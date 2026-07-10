#pragma once

/*
     Defines dispatches for global UI events
     triggered from UI classes.
*/


//Engine imports.
#include "CoreMinimal.h"


//Forward declares.
class UDragDropOperation;
class UItemInstance;
class UUIDraggableBase;


/*
    Forwards the UDragDropOperation during a drag event to all 
    listeners.

    @param InDragOperation: pointer to the current drag and drop
    operation.
*/
DECLARE_MULTICAST_DELEGATE_OneParam(FForwardDragOperationSignature, UDragDropOperation* InDragOperation);


/*
    Forward the UDragDropOperation during a drop event to all
    listeners.

    @param InDropOperation: pointer to the current drag and drop
    operation.
*/
DECLARE_MULTICAST_DELEGATE_OneParam(FForwardDropOperationSignature, UDragDropOperation* InDropOperation);



/*
     Forwards an item instance through the payload when an item is currently
     being dragged, and is rotated.

     @param RotatedItem: pointer to the rotated item
     instance.

     @param DraggingWidget: pointer to the widget that 
     is currently being dragged.

     @param bRotated: true if the item was rotated 90 degrees; essentailly
     if it was changed, false if the item was reset.
*/
DECLARE_MULTICAST_DELEGATE_ThreeParams(FForwardRotatedItemSignature, UItemInstance* RotatedItem, UUIDraggableBase* DraggingWidget,bool bRotated);



struct FUISubsystemDelegates
{
    FForwardDragOperationSignature ForwardDragOperation;
    FForwardDropOperationSignature ForwardDropOperation;
    FForwardRotatedItemSignature ForwardRotatedItem;
};