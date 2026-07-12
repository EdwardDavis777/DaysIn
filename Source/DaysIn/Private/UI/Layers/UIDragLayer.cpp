//Engine imports.
#include "UI/Layers/UIDragLayer.h"


//Custom component imports.
#include "UI/Layers/Controllers/DragLayerController.h"
#include "CustomClasses/Components/Factory/NativeUITemplate.h"


//Utility imports.
#include "SubsystemUtilitys/SubsystemUtility.h"

//Subsystem imports.
#include "Subsystems/UI/UISubsystem.h"



void UUIDragLayer::NativeConstruct()
{
	Super::NativeConstruct();

	DragLayerController = NativeUITemplate::CreateDefaultUIComponent<UDragLayerController>(GetWorld(), this);
	UISubsystem = SubUtility::FindSub<UUISubsystem>(GetWorld());
	BindDelegates();
}

void UUIDragLayer::BindDelegates()
{
	if (!UISubsystem) return;

	UISubsystem->UISubsystemDispatches.ForwardDropOperation.AddUObject(this, &UUIDragLayer::RemoveFromLayer);
	UISubsystem->UISubsystemDispatches.CancelDragAndDrop.AddUObject(this, &UUIDragLayer::RemoveOnCancel);
}


void UUIDragLayer::NativeTick(const FGeometry& MyGeometry, const float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	if (bFollowCursor && DragLayerController)
	{
		DragLayerController->FollowCursor(DraggingWidgetSlot,MyGeometry,DragSize.X,DragSize.Y);
	}
}



/*
							           Drag layer event functions.
*/

void UUIDragLayer::AddToLayer(UUserWidget* WidgetToAdd, const double& XSize, const double& YSize, int32 ZOrder, bool bTrackCursor)
{
	if (!WidgetToAdd || !DragLayerController) return;
	
	DraggingWidget = DragLayerController->HandleAdd(WidgetToAdd,DraggingWidgetSlot, XSize, YSize, ZOrder);
	bFollowCursor = bTrackCursor;
}

void UUIDragLayer::RemoveFromLayer(UDragDropOperation* InOperation)
{
	if (!InOperation || !DragLayerController) return;
	
	DragLayerController->HandleRemove(DraggingWidget);
	bFollowCursor = false;
}

void UUIDragLayer::RemoveOnCancel()
{
	if (!DraggingWidget || !DragLayerController) return;
	
	DragLayerController->HandleCancel(DraggingWidget);
	bFollowCursor = false;
}



/*
									             Mutators.
*/

void UUIDragLayer::SetDragSize(const double& SizeX, const double& SizeY)
{
	DragSize = FVector2D(SizeX, SizeY);
}

void UUIDragLayer::SetDraggingSlot(UCanvasPanelSlot* DragPanelSlot)
{
	if (!DragPanelSlot) return;
	DraggingWidgetSlot = DragPanelSlot;
}



/*
									             Accessors.
*/

TObjectPtr<USizeBox>& UUIDragLayer::GetSizeBox()
{
	return RootSizeBox;
}

TObjectPtr<UCanvasPanel>& UUIDragLayer::GetGroupPanel()
{
	return GroupPanel;
}

TObjectPtr<UCanvasPanelSlot>& UUIDragLayer::GetDraggingWidgetSlot()
{
	return DraggingWidgetSlot;
}