#pragma once

/*

    Defines static default collectable storage properties
	such as grid size etc.

	This data is defined inside of the CollectableStorageDataAsset
	class.

*/


//Engine imports.
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CollectableStorageProperties.generated.h"


USTRUCT(BlueprintType)
struct FCollectableStorageProps
{
	GENERATED_BODY()

	
	/*
	    Defines how many columns, and rows this storage instance
		will implement.
	*/
	UPROPERTY(EditAnywhere)
	FIntPoint StorageSize;


	FCollectableStorageProps()
	: StorageSize()
	{ }
};



UCLASS()
class DAYSIN_API UCollectableStorageProperties : public UObject
{
	GENERATED_BODY()
};
