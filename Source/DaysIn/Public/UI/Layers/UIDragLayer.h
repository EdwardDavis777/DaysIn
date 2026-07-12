#pragma once


/*

      Defines class defaults for a UI layer that is used for rendering 
	  draggable widgets; widgets that are currently being dragged by the
	  player.

*/



//Engine imports.
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIDragLayer.generated.h"



//Forward declares.
class USizeBox;
class UBorder;
class UCanvasPanel;
class UCanvasPanelSlot;

class UDragLayerController;
class UUISubsystem;


UCLASS()
class DAYSIN_API UUIDragLayer : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;
	void BindDelegates();


	/*
	                               Drag layer components.
	*/
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<USizeBox> RootSizeBox;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UBorder> MainBorder;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UCanvasPanel> GroupPanel;
      


	/*
	                                Custom components.
	*/
	UPROPERTY()
	TObjectPtr<UDragLayerController> DragLayerController;


	/*
	                               Cached components.
	*/
	UPROPERTY()
	TObjectPtr<UUserWidget> DraggingWidget;
    
	UPROPERTY()
	TObjectPtr<UCanvasPanelSlot> DraggingWidgetSlot;

	UPROPERTY()
	FVector2D DragSize = FVector2D::ZeroVector;

	UPROPERTY()
	TObjectPtr<UUISubsystem> UISubsystem;


	/*
	                                Drag layer states.
	*/
	UPROPERTY()
	bool bFollowCursor = true;

public:

	/*
	                             Drag layer event functions.
	*/

	/*
	      Adds a widget to the drag layer, and caches the current pointer
		  in the drag layer.

		  @param WidgetToAdd: pointer to the current widget you 
		  wish to add to the drag layer.

		  @param SizeX: X size of the widget panel
		  slot when added.

		  @param SizeY: Y size of the widget panel
		  slot when added.

		  @param ZOrder: level of Z order you wish for the dragging
		  widget, defaulted very high to ensure it does not get 
		  hidden.

		  @param bFollowCursor: if true, the widget will follow the cursor
		  directly at the center, if false, then it will not follow
		  the cursor at all. Defaulted to true.
	*/
	void AddToLayer(UUserWidget* WidgetToAdd,const double& SizeX, const double& SizeY,int32 ZOrder = 999, bool bTrackCursor = true);


	/*
	       Removes a dragging widget from the render layer during a 
		   drop event. This function is binded to a dispatch that gets triggered
		   during a drop event.

		   @param InOperation: pointer to the current drop 
		   operation.
	*/
	void RemoveFromLayer(UDragDropOperation* InOperation);

	/*
	      Removes any dragging widget from the layer when a drag cancel
		  event is dispatched.
	*/
	void RemoveOnCancel();


	/*
	                              Engine overrides.
	*/
	virtual void NativeTick(const FGeometry& MyGeometry, const float DeltaTime) override;


	/*
	                                  Mutators.
	*/
	void SetDragSize(const double& SizeX, const double& SizeY);
	void SetDraggingSlot(UCanvasPanelSlot* DragPanelSlot);

	/*
	                                 Accessors.
	*/
	FORCEINLINE const FVector2D& GetDragSize() const
	{
		return DragSize;
	}

	TObjectPtr<USizeBox>& GetSizeBox();
	TObjectPtr<UCanvasPanel>& GetGroupPanel();
	TObjectPtr<UCanvasPanelSlot>& GetDraggingWidgetSlot();
};