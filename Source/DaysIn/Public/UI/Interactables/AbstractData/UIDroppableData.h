#pragma once

/*
      Defines all droppable data and configurations, such as 
	  run-time data, including a map of stored draggable widgets, and
	  their assocaited instances etc.
*/


//Engine imports.
#include "CoreMinimal.h" 
#include "UObject/NoExportTypes.h"
#include "UIDroppableData.generated.h"


//Forward declares.
class UItemInstance;
class UUIDraggableBase;



USTRUCT(BlueprintType)
struct FDroppableRuntimeData
{
	GENERATED_BODY()

	
	/*
	    Stores all drag widgets stored inside of this droppable widget
		instance.
	*/
	UPROPERTY(VisibleAnywhere)
	TMap<TObjectPtr<UItemInstance>, TObjectPtr<UUIDraggableBase>> StoredDragWidgets;

   
	FDroppableRuntimeData()
	: StoredDragWidgets()
	{ }
};



UCLASS()
class DAYSIN_API UUIDroppableData : public UObject
{
	GENERATED_BODY()
};
