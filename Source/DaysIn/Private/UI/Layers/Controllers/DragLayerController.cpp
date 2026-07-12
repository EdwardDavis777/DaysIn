//Engine imports.
#include "UI/Layers/Controllers/DragLayerController.h"

//Component imports.
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "Blueprint/DragDropOperation.h"


//Other imports.
#include "UI/Layers/UIDragLayer.h"




//Static data imports.
#include "StaticData/UI/WidgetMath.h"



//Utility imports.
#include "SubsystemUtilitys/SubsystemUtility.h"


//Subsystem imports.
#include "Subsystems/UI/UISubsystem.h"



void UDragLayerController::Initialize(UWorld* WorldContext, UUserWidget* OwnerWidget)
{
	Super::Initialize(WorldContext, OwnerWidget);
	DragLayer = FindOwner<UUIDragLayer>();
}



/*
							     Drag layer event functions.
*/

UUserWidget* UDragLayerController::HandleAdd(UUserWidget* WidgetToAdd, TObjectPtr<UCanvasPanelSlot>& AddedPanelSlot,const double& XSize, const double& YSize, const int32& ZOrder)
{
	if (!WidgetToAdd || !DragLayer) return nullptr;

	if (auto* ParentSlot = Cast<UCanvasPanelSlot>(DragLayer->GetGroupPanel()->AddChild(WidgetToAdd)))
	{
		SetDragSlotSize(XSize, YSize,ZOrder, ParentSlot);
		AddedPanelSlot = ParentSlot;
		return WidgetToAdd;
	}
	return nullptr;
}

void UDragLayerController::HandleRemove(TObjectPtr<UUserWidget>& DraggingWidget)
{
	if (!DraggingWidget) return;

	DraggingWidget->SetVisibility(ESlateVisibility::Collapsed);
	DraggingWidget->RemoveFromParent();
	DraggingWidget = nullptr;  
}

void UDragLayerController::HandleCancel(TObjectPtr<UUserWidget>& DraggingWidget)
{
	if (!DraggingWidget) return;

	DraggingWidget->SetVisibility(ESlateVisibility::Collapsed);
	DraggingWidget->RemoveFromParent();
	DraggingWidget = nullptr;
}


void UDragLayerController::FollowCursor(TObjectPtr<UCanvasPanelSlot>& ParentSlot, const FGeometry& InGeometry, const double& XSize,const double& YSize,double CenterOffset)
{
	if (!ParentSlot) return;

	const FVector2D AbsMousePosition = FSlateApplication::Get().GetPlatformCursor()->GetPosition();
	const FVector2D CenterCenter = InGeometry.AbsoluteToLocal(AbsMousePosition);
	const FVector2D PixelSize = FVector2D(XSize * WidgetMath::TileSize, YSize * WidgetMath::TileSize);
	const FVector2D Offset = PixelSize * CenterOffset;
	ParentSlot->SetPosition(CenterCenter - Offset);
}




/*
									 Helper function.
*/

void UDragLayerController::SetDragSlotSize(const double& XSize, const double& YSize, const int32& ZOrder, UCanvasPanelSlot* ParentSlot)
{
	if (!ParentSlot || !DragLayer) return;

	const FVector2D SlotSize = FVector2D(WidgetMath::TileSize * XSize, WidgetMath::TileSize * YSize);
	ParentSlot->SetSize(SlotSize);
	ParentSlot->SetZOrder(ZOrder);
	DragLayer->SetDragSize(XSize, YSize);
}