#pragma once


/*

      Defines all default item data that is subject to 
	  change. All item runtime data structs are derived from
	  this struct below.

*/

//Data imports.
#include "ItemUIRuntimeData.h"
#include "Save/Packages/Objects/Abstracts/SPKGSubInstance.h"



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

	UPROPERTY(SaveGame)
	TArray<FSPKGSubInstance> SubInstancePackages;
	


	/*
	     Populated at runtime, used to store inner instance relationships
		 that will later be serialized during save events.
	*/
	UPROPERTY()
	TMap<TObjectPtr<UObject>, FIntPoint> SubInstances;

	/*
	      Map of deserialized inner actors and their associated save package, sent back during
		  a load save event. Populated during at a post deserialize 
		  event.
	*/
	UPROPERTY()
	TMap<TObjectPtr<AActor>,FSPKGSubInstance> DeserializedInners;



	FItemRunTimeData() 
	: SubInstancePackages(), SubInstances()
	{ }
};