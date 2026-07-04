#pragma once

/*

	Defines static default collectable storage properties
	UI such as its inventory widget class type etc.

	This data is defined inside of the CollectableStorageDataAsset
	class.

*/

//Engine imports.
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CollectableStorageUIProperties.generated.h"


//Forward declares.
class UUICollectableStorageInventory;


USTRUCT(BlueprintType)
struct FCollectableStorageUIProps
{
	GENERATED_BODY()


	/*
	    Defines the class type this storage collectable will use for
		its inventory widget, grid, etc.
	*/
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUICollectableStorageInventory> InventoryWidgetClass;




	FCollectableStorageUIProps()
	: InventoryWidgetClass()
	{ }
};

UCLASS()
class DAYSIN_API UCollectableStorageUIProperties : public UObject
{
	GENERATED_BODY()
	
};