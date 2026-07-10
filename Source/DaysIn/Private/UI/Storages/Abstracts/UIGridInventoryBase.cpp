//Engine imports.
#include "UI/Storages/Abstracts/UIGridInventoryBase.h"


//Component imports.
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/SizeBox.h"
#include "Components/CanvasPanel.h"


//Other imports.
#include "Items/Abstracts/ItemInstance.h"
#include "UI/Interactables/Abstracts/GlobalEvents/DraggableTemplates/DraggableTemplates.h"
 


void UUIGridInventoryBase::InitializeGrid(int32 X, int32 Y, UObject* OwnerObject)
{ 
	if (!RootSizeBox || !OwnerObject) return;

	Columns = X;
	Rows = Y;

	FVector2D GridSize = FVector2D(Columns * TileSize, Rows * TileSize);
	RootSizeBox->SetWidthOverride(GridSize.X);
	RootSizeBox->SetHeightOverride(GridSize.Y);
	Owner = OwnerObject;
}


/*
										    UI event functions.
*/

void UUIGridInventoryBase::HookDragOverEvent(const FGeometry& InGeometry, const FDragDropEvent& InDragEvent, UDragDropOperation* InOperation)
{
	if (UItemInstance* DraggingInstance = DraggableTemplate::GetPayloadInstance<UUIDraggableBase>(InOperation))
	{
		const FVector2D LocalMousePosition = InGeometry.AbsoluteToLocal(InDragEvent.GetScreenSpacePosition());
		const FVector2D DraggedPixelSize = FVector2D(DraggingInstance->GetDynamicUISize() * TileSize);
		const FVector2D MouseGridOffset = LocalMousePosition - (DraggedPixelSize * 0.5f);

		MouseGridPosition = FIntPoint(
		FMath::RoundToInt(MouseGridOffset.X / TileSize),
		FMath::RoundToInt(MouseGridOffset.Y / TileSize));
    }
}


/*
                                           Paint event functions.
*/

int32 UUIGridInventoryBase::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	FPaintContext PaintContext(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);


	for (int32 X{}; X <= Columns; X++)
	{
		int32 xPos{ X * TileSize };
		UWidgetBlueprintLibrary::DrawLine(PaintContext, FVector2D(xPos, 0.0f),
		FVector2D(xPos, Rows * TileSize),GridLineColor);
	}

	for (int32 Y{}; Y <= Rows; Y++)
	{
		int32 yPos{ Y * TileSize };
		UWidgetBlueprintLibrary::DrawLine(PaintContext, FVector2D(0, yPos),
		FVector2D(Columns * TileSize, yPos), GridLineColor);
	}
	return int32();
}