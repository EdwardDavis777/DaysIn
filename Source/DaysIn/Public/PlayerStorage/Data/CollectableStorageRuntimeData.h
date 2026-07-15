#pragma once



//Engine imports.
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Items/Data/ItemRuntimeData.h"
#include "CollectableStorageRuntimeData.generated.h"




USTRUCT(BlueprintType)
struct FStorageRuntimeData : public FItemRunTimeData
{
	GENERATED_BODY()
};