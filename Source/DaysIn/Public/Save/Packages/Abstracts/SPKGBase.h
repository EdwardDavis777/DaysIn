#pragma once

/*

     Defines save packaged defaults; all save packages are derived
     from this class, or their parent will be.

*/


//Engine imports.
#include "CoreMinimal.h"
#include "SPKGBase.generated.h"



USTRUCT(BlueprintType)
struct FSPKGBase
{
    GENERATED_BODY()


    UPROPERTY(SaveGame)
    TArray<uint8> ByteData;

    FSPKGBase()
    : ByteData()
    { }
};