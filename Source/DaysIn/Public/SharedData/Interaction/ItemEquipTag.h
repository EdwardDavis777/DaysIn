#pragma once

/*

     Defines a shared enumerator that holds item equipment 
	 tags. The tags are shared between storage objects, and items;
	 allows containers to define what objects they can store, and allows
	 items to define what type of storage objects they should be stored
	 in.

*/


//Engine imports.
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemEquipTag.generated.h"



UENUM(BlueprintType)
enum class EEquipTag : uint8
{
	NONE         UMETA(DisplayName = "None"),

	PRIMARY      UMETA(DisplayName = "Primary"),
	SECONDARY    UMETA(DisplayName = "Secondary"),

	BACKPACK     UMETA(DisplayName = "Backpack")
};
UCLASS()
class DAYSIN_API UItemEquipTag : public UObject
{
	GENERATED_BODY()
	
};