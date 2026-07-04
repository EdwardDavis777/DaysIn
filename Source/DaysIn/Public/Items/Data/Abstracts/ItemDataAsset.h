#pragma once


/*
     Defines default static item object data structs
	 that are immutable at runtime.

	 Note: each derived item objects data is derived from this asset
	 and implements their own types.
	   
*/ 
 
 
//Data imports.
#include "Items/Data/ItemProperties.h" 
#include "Items/Data/ItemUIProperties.h"
#include "Items/Data/ItemPhysicsProperties.h"

//Engine imports.
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"



UCLASS()
class DAYSIN_API UItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data| Properties")
	FItemProps ItemProperties;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data| UI")
	FItemUIProps ItemUIProperties;
   
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data| Physics")
	FItemPhysicsProps ItemPhysicsProperties;
};