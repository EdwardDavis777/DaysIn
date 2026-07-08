//Engine imports.
#include "UI/Interactables/Abstracts/GlobalEvents/DraggableColorMethods/ColorMethods.h"

//Component imports.
#include "Components/Border.h"

//Other imports.
#include "UI/Interactables/Abstracts/UIDraggableBase.h" 




namespace ColorMethod
{
	void SetDefaultColor(UUIDraggableBase* DraggedIcon)
	{
		if (!DraggedIcon) return;
		DraggedIcon->GetBorder()->SetBrushColor(DraggedIcon->ColorData.DefaultBorderColor);
	}

	void SetCanPlaceColor(UUIDraggableBase* DraggedIcon)
	{
		if (!DraggedIcon) return;
		DraggedIcon->GetBorder()->SetBrushColor(DraggedIcon->ColorData.CanPlaceColor);
	}

	void SetCannotPlaceColor(UUIDraggableBase* DraggedIcon)
	{
		if (!DraggedIcon) return;
		DraggedIcon->GetBorder()->SetBrushColor(DraggedIcon->ColorData.CannotPlaceColor);
	}
}