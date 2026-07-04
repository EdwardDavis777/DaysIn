#pragma once

/*

     Defines class defaults for all item instance related
     save packages.

*/


//Engine imports.
#include "Save/Packages/Abstracts/SPKGBase.h"
#include "CoreMinimal.h"
#include "SPKGInstanceBase.generated.h"


//Forward declares.
class UItemDataAsset;
class UItemInstance;
class AItemBase;




USTRUCT(BlueprintType)
struct FSPKGInstanceBase : public FSPKGBase
{
    GENERATED_BODY()

    UPROPERTY()
    TSubclassOf<AItemBase> ItemClass;

    FSPKGInstanceBase()
    : ItemClass()
    { }
};