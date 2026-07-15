#pragma once

/*

      Defines generic save package configurations for sub instances;
      used during recursive serialization of objects at runtime.

*/


//Engine imports.
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Save/Packages/Abstracts/SPKGBase.h"
#include "SPKGSubInstance.generated.h"


//Forward declares.
class AItemBase;



USTRUCT(BlueprintType)
struct FSPKGSubInstance : public FSPKGBase
{
    GENERATED_BODY()

    UPROPERTY(SaveGame)
    TSubclassOf<AItemBase> ItemClass;

    UPROPERTY(SaveGame)
    FIntPoint Position;


    FSPKGSubInstance()
    : ItemClass(),Position(FIntPoint())
    { }
};