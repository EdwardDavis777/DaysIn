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
class UUIDraggableBase;
class UDragDropOperation;
class UItemInstance;
class UCanvasPanel;


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
	     Constructs an item instance icon inside of the event 
		 owner.

		 @Instance: pointer to the instance you wish to 
		 constructed an icon from.

		 @StoredWidgets: reference to the droppables stored widgets
		 cache.

		 @param Position: 2D position; needed for proper placement
		 in the event owner.

		 @param EventOwner: pointer to the widget instance that owns
		 the store event.

		 @return UUIDraggableBase: pointer to the constructed 
		 widget back to the caller.
	*/
	void HandleStore(UItemInstance* Instance,TMap<TObjectPtr<UItemInstance>,TObjectPtr<UUIDraggableBase>>& StoredWidget, const FIntPoint& Position,UUIDroppableBase* EventOwner);


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
	                               Helper functions.
	*/

	/*
	     Fully initializes a new constructed item icon, adds it to the passed
		 parent panel, and sets its new size.

		 @param ParentPanel: pointer to the canvas panel you wish to add
		 the new icon into.

		 @param NewIcon: pointer to the new constructed item icon
		 you wish to add to the parent panel.

		 @param Instance: pointer to the assocaitd item instance 
		 with the new icon.

		 @param Position: 2D position; where to place the new icon in the 
		 parent panel.

	*/
	void InitializeNewIcon(UCanvasPanel* ParentPanel,UUIDraggableBase* NewIcon,UItemInstance* Instance,const FIntPoint& Position);


	/*
	                         UDroppableUIComponent components.
	*/
	UPROPERTY()
	TObjectPtr<UUIDroppableBase> Droppable;
};