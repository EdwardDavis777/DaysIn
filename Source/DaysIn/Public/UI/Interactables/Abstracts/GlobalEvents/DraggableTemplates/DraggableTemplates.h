#pragma once

/*

     Defines simple helper templates for UIDraggable events, such 
     as finding assocaited item instances through payload's etc.

*/


//Other imports.
#include "Blueprint/DragDropOperation.h"
#include "UI/Interactables/Abstracts/UIDraggableBase.h"

//Engine imports.
#include "CoreMinimal.h"



//Forward declares.
class UItemInstance;


namespace DraggableTemplate
{

    /*
          Returns a item instance from a draggable instance found
          inside of the drag and drop payload.

          @param InOperation: pointer to the current drag and drop
          operation.

          @tparam UUIDraggableBase: T must be derived a UUIDraggableBase, or the 
          build will fail.

          @return UItemInstance: pointer to an assocaited item instance 
          to the caller.
    */
    template<typename TPayload>
    UItemInstance* GetPayloadInstance(UDragDropOperation* InOperation)
    {
        if (!InOperation || !InOperation->Payload) return nullptr;
        static_assert(TIsDerivedFrom<TPayload, UUIDraggableBase>::IsDerived, "T must be a UUIDraggableBase");
        
        if (TPayload* Dragged = Cast<TPayload>(InOperation->Payload))
        {
            if (auto* AssocaitedInstance = Cast<UItemInstance>(Dragged->GetAssocaitedInstance()))
            {
                return AssocaitedInstance;
            }
        }
        return nullptr;
    }


    /*
         Performs a simple cast to check if the current payload is pointing to 
         a draggable instance.

         @param InOperation: pointer to the current drag and drop
         operation.
         
         @tparam UUIDraggableBase: T must be a UUIDraggableBase.

         @return UUIDraggableBase: pointer to the payload draggable widget
         with the class type provided by the caller.
    */
    template<typename TPayload>
    TPayload* GetPayload(UDragDropOperation* InOperation)
    {
        if (!InOperation || !InOperation->Payload) return nullptr;

        static_assert(TIsDerivedFrom<TPayload, UUIDraggableBase>::IsDerived, "T must be a UUIDraggableBase");
        if (TPayload* Payload = Cast<TPayload>(InOperation->Payload))
        {
            return Payload;
        }
        return nullptr;
    }
}