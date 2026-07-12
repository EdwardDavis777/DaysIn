#pragma once

/*

      Component controller for run-time events that occure inside of 
	  the UIDragLayer widget instance.

*/


//Engine imports.
#include "CoreMinimal.h"
#include "CustomClasses/Components/NativeUIComponent.h"
#include "DragLayerController.generated.h"



//Forward declares.
class UUIDragLayer;
class UCanvasPanelSlot;
class UDragDropOperation;



UCLASS()
class DAYSIN_API UDragLayerController : public UNativeUIComponent
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(UWorld* WorldContext, UUserWidget* OwnerWidget) override;

	
	/*
	                           Drag layer event functions.
	*/
	
	/*
	       Adds the passed widget to the UIDragLayer group panel, and sets is desired size
		   given the X and Y size from the caller.

		   @param WidgetToAdd: pointer to the widget that 
		   was added.

		   @param AddedPanelSlot: pointer reference to an empty
		   panel slot, that is set after the widget is added.

		   @param XSize: X size of the widget dimensions.

		   @param YSize: Y size of the widget dimensions.

		   @param ZOrder: Z level of the added 
		   widget.

		   @return UUserWidget: a pointer to the added widget if 
		   this function succeeds.
	*/
	UUserWidget* HandleAdd(UUserWidget* WidgetToAdd,TObjectPtr<UCanvasPanelSlot>& AddedPanelSlot, const double& XSize, const double& YSize, const int32& ZOrder);


	/*
	       Removes the dragging widget from its parent, and from visibility
		   and resets drag states.

		   @param DraggingWidget: pointer to the current 
		   dragging widget.
	*/
	void HandleRemove(TObjectPtr<UUserWidget>& DraggingWidget);


	/*
	    Removes the dragging widget from its parent, and from visibility
		and resets drag states if a drag event is canceled.

		 @param DraggingWidget: pointer to the current 
		 dragging widget.
	*/
	void HandleCancel(TObjectPtr<UUserWidget>& DraggingWidget);

	/*
	      Sets the dragging widgets render translation to follow the controller 
		  cursor during a drag event.

		  @param ParentSlot: pointer to the dragging widgets
		  panelt slot.

		  @param InGeometry: reference to the current widgets
		  geometry.

		  @param XSize: X size of the widget dimensions.

		  @parma YSize: Y size of the widget dimensions.

		  @param CenterOffset: simply the offset from the 
		  center, defaulted to 0.5f as its just sort of standard.
	*/
	void FollowCursor(TObjectPtr<UCanvasPanelSlot>& ParentSlot,const FGeometry& InGeometry,const double& XSize,const double& YSize,double CenterOffset = 0.5f);


	/*
	                                Helper function.
	*/


	/*
	       Sets the size of the drag widgets parent slot, and sets 
		   the cached drag size.

		   
		   @param XSize: X size of the widget dimensions.

		   @param YSize: Y size of the widget dimensions.

		   @param ZOrder: reference to the wished
		   ZOrder.

		   @param ParentSlot: pointer to the parent
		   slot the drag widget is added to.
	*/
	void SetDragSlotSize(const double& XSize, const double& YSize, const int32& ZOrder,UCanvasPanelSlot* ParentSlot);

private:

	/*
	                                   Components.
	*/
	UPROPERTY()
	TObjectPtr<UUIDragLayer> DragLayer;
};