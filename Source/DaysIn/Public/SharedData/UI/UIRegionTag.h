#pragma once

/*
     Defines UI region tags for the UI player main, and other widgets
	 that get added to it during run-time.
*/


//Engine imports.
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UIRegionTag.generated.h"



UENUM(BlueprintType)
enum class ERegionTag : uint8
{
	NONE                   UMETA(DisplayName = "None"),
	BACKPACKREGION         UMETA(DisplayName = "BackpackRegion")
};

UCLASS()
class DAYSIN_API UUIRegionTag : public UObject
{
	GENERATED_BODY()
	
};
