#pragma once

/*
     Defines default run-time logic for all UIDraggableBase
	 widget instances.
*/



//Engine imports.
#include "CoreMinimal.h"
#include "CustomClasses/Components/NativeUIComponent.h"
#include "DraggableUIComponent.generated.h"



//Forward declares.
class UUIDraggableBase;
class UDragDropOperation;
class UItemInstance;
class UPlayerUISubsystem;

 

UCLASS()
class DAYSIN_API UDraggableUIComponent : public UNativeUIComponent
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(UWorld* WorldContext, UUserWidget* OwnerWidget) override;



	/*
	                            Draggable event functions.
	*/


	/*
	     Simply initializes class defaults, such as the drag widgets
		 image etc.
	*/
	void InitDefaults(UUIDraggableBase* DragInstance, UItemInstance* Instance);

    
	/*
	     Creates a copied widget for drag visuals using the event owner as a 
		 reference.
  
		 @param InOperation: pointer to the current drag and drop
		 operation.

		 @param EventOwner: pointer to the widget that owns the 
		 drag event.

		 @param OwnerInstance: pointer to the item instance assocaited
		 with the event widget.
	*/
	void MakeDragWidget(UDragDropOperation* InOperation,UUIDraggableBase* EventOwner,TObjectPtr<UItemInstance>& OwnerInstance);


	/*
	      Handles rotating, and setting the current state of a dragging widget.
		  If its currently rotating, it will set the dragging widgets state for later
		  drop events, or reset the rotation of the dragging widget.

		  @param AssocaitedInstance: pointer to the assocaited item instance
		  for the dragging widget.

		  @param DraggingWidget: pointer to the current dragging
		  widget.

		  @param bRotated: truthy whether the widget has been rotated, or reset
		  to a default state.
	*/
	void HandleRotation(UItemInstance* AssocaitedInstance, UUIDraggableBase* DraggingWidget, bool bRotated);


	/*
		 Simply ensures that dragged instances have default settings triggered during
		 a drag event. Such as resetting rotation states etc.

		 @param InOperation: pointer to the current drag and
		 drop event
	*/
	void HandleDragDefaults(UDragDropOperation* InOperation);


	/*
	     Triggeres a force spawn event if a drag is interrupted for some 
		 reason.

		 @param InOperation: pointer to the current drag
		 drop operation.

		 @param PlayerUISubsystem: pointer to the player ui subsytem
		 for force spawn dispatching.
	*/
	void HandleDragCancelled(UDragDropOperation* InOperation, UPlayerUISubsystem* PlayerUISubsystem);
    


	/*
	    Enables hover glow for the owner instance of this component
		called when a players mouse hovers over a draggable widget, and 
		if it can be dragged.

		@param HoverColor: reference to the color you wish to change
		the border to when the widget is draggable.
	*/
	void SetHoverGlow(const FLinearColor& HoverColor);


	/*
	    Disables hover glow for the owner instance, and reverts it back
		to its default border color.

		@param DefaultBorderColor: reference to the widgets default border
		color you wish to change back to.
	*/
	void RemoveHoverGlow(const FLinearColor& DefaultBorderColor);

	/*
	     Resets class defaults for a general draggable widget 
		 instance.

		 @param DefaultBorderColor: reference to the widgets default border
		 color you wish to change back to.
	*/
	void ResetDefaults(const FLinearColor& DefaultBorderColor);

	/*
	                                 Helper functions. 
	*/

	/*
	    Sets the size of a drag widget from its item instance data.

		@param DragWidget: pointer to the widget whose size you 
		wish to set.

		@param Instance: pointer to the instance assoicated with the
		drag widget.
	*/
	void SetDragWidgetSize(UUIDraggableBase* DragWidget, TObjectPtr<UItemInstance>& Instance);


	/*
	    Copies over all drag widget defaults from a reference widget, over to 
		a valid empty copy.

		@param Reference: pointer to the widget whose feilds you
		wish to copy.

		@param OwnerInstnace: pointer to an item instance; will be 
		copied over to the copy widget.

		@param Copy: pointer to the empty instance whose feilds you
		wish to set through the reference pointer.
	*/
	void CopyDefaults(UUIDraggableBase* Reference, UUIDraggableBase* Copy, TObjectPtr<UItemInstance>& OwnerInstance);
private:

	/*
	                           UDraggableUIComponent components.
	*/
	UPROPERTY()
	TObjectPtr<UUIDraggableBase> DraggableWidget;
};