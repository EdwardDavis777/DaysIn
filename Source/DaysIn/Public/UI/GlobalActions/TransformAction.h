#pragma once

/*

     Defines global widget transform methods, such as location
     translations, rotations etc.

*/


//Engine imports.
#include "CoreMinimal.h"

//Forward declares.
class UWidget;


namespace Transform
{
    struct Rot
    {
        /*
             Rotates the passed widget -90 degrees.

             @param WidgetToRotated: pointer to the widget 
             you wish to rotate.

             @return int32(): returns the rotated angle
             back as an int.
        */
        static int32 RotNeg90(UUserWidget* WidgetToRotate);

        /*
             Rotates a UWidget to -90 degrees.

             @param WidgetToRotate: pointer to the widget
             you wish to rotate.

             @return int32(): returns the rotated angle
             back as an int.
        */
        static int32 RotNeg90(UWidget* WidgetToRotate);


        /*
            Resets a widgets rotation angle back to
            0.

            @param WidgetToRotate: pointer to the widget you
            wish to rotate.

            @return int32(): returns the rotated angle back
            as an int.
        */
        static int32 Rot0(UUserWidget* WidgetToRotate);


        /*
            Resets a UWidget rotation angle back to
            0.

            @param WidgetToRotate: pointer to the widget you
            wish to rotate.

            @return int32(): returns the rotated angle back
            as an int.
        */
        static int32 Rot0(UWidget* WidgetToRotate);
    };
}