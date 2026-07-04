#pragma once

/*
     Defines simple global threshold values used for 
     comparing a weapons actual thresold.
*/


//Engine imports.
#include "CoreMinimal.h"


namespace Thresholds
{
    struct Num
    {
       static inline constexpr int32 Full = 100;
       static inline constexpr int32 Medium = 65;
       static inline constexpr int32 Low = 45;
    };

    struct Color
    {
        inline const static FLinearColor FullColor = FLinearColor::Green;
        inline const static FLinearColor MediumColor = FLinearColor::Yellow;
        inline const static FLinearColor LowColor = FLinearColor::Red;
    };
}