#pragma once

/*
     Defines all static collectable storage 
	 data structs.
*/


//Other imports.
#include "CollectableStorageProperties.h"
#include "CollectableStorageUIProperties.h"



//Engine imports.
#include "CoreMinimal.h"
#include "Items/Data/Abstracts/ItemDataAsset.h"
#include "CollectableStorageDataAsset.generated.h"




UCLASS()
class DAYSIN_API UCollectableStorageDataAsset : public UItemDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Storage Properties")
	FCollectableStorageProps CollectableStorageProperties;
    

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Storage UI Properties")
	FCollectableStorageUIProps CollectableStorageUIProperties;
};