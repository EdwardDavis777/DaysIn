#pragma once


/*

     Defines default item UI data that is subject to change
     at runtime.

*/


//Engine imports.
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemUIRuntimeData.generated.h"



USTRUCT(BlueprintType)
struct FItemUIRunTimeData
{
    GENERATED_BODY()


    UPROPERTY(SaveGame)
    FIntPoint RotatedSize;

    UPROPERTY(SaveGame)
    bool bItemRotated;

    FItemUIRunTimeData()
    : bItemRotated(false),RotatedSize()
    { }
};