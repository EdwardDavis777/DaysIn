#pragma once

/*

      Defines a load of methods for changing draggable border
      colors, such as placement color, and different ways of changing
      the color, either through payloads, direct pointers etc.

*/


 
//Engine imports.
#include "CoreMinimal.h"


//Forward declares.
class UUIDraggableBase;



namespace ColorMethod
{

    /*
         Resets the dragged icons border color back to 
         its default color.

         @param DraggedIcon: pointer to the dragged icon
         you wish to change.
    */
    void SetDefaultColor(UUIDraggableBase* DraggedIcon);

    /*
         Changes the dragged icon to a can place color when dragged
         over some user interface where it can be dropped/placed.

         @param DraggedIcon: pointer to the dragged icon
         you wish to change.
    */
    void SetCanPlaceColor(UUIDraggableBase* DraggedIcon);


    /*
         Changes the dragged icon to a cannot place color when dragged
         over some user interface where it cannot be dropped/placed.

         @param DraggedIcon: pointer to the dragged icon
         you wish to change.
    */
    void SetCannotPlaceColor(UUIDraggableBase* DraggedIcon);
}