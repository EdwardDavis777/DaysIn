#pragma once


/*

      Defines all default item data that is subject to 
	  change. All item runtime data structs are derived from
	  this struct below.

*/

//Data imports.
#include "ItemUIRuntimeData.h"


//Engine imports.
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemRuntimeData.generated.h"




USTRUCT(BlueprintType)
struct FItemRunTimeData
{
	GENERATED_BODY()

	UPROPERTY(SaveGame)
	FItemUIRunTimeData ItemUIRuntimeData;
};