#pragma once


/*
	 Defines default run-time logic for all UIDroppableBase
	 widget instances.
*/



//Engine imports.
#include "CoreMinimal.h"
#include "CustomClasses/Components/NativeUIComponent.h"
#include "DroppableUIComponent.generated.h"


//Forward declares.
class UUIDroppableBase;
class UDragDropOperation;



UCLASS()
class DAYSIN_API UDroppableUIComponent : public UNativeUIComponent
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(UWorld* WorldContext, UUserWidget* OwnerWidget) override;


	/*
	                           Droppable event functions.
	*/

	/*
	    Handles drop events for its owning widget, then calls the
		store dropped event function.

		@param InOperation: pointer to the current drag drop 
		operation.

		@return TRUE/FALSE: true if the drop event was successful, false
		if something when wrong.
	*/
	bool HandleDrop(UDragDropOperation* InOperation);

private:

	/*
	                         UDroppableUIComponent components.
	*/
	UPROPERTY()
	TObjectPtr<UUIDroppableBase> Droppable;
};