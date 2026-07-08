//Engine imports.
#include "UI/Player/UIRegionPanel.h"

//Component imports.
#include "Components/CanvasPanel.h"

//Other imports.
#include "UI/Interactables/Abstracts/UIDroppableBase.h"



void UUIRegionPanel::NativeConstruct()
{
	Super::NativeConstruct();
} 



/*
							   Region event functions.
*/

void UUIRegionPanel::AddToRegion(UUIDroppableBase* WidgetToAdd)
{
	if (!WidgetToAdd || !RegionPanel) return;

	if (!RegionChildren.Contains(WidgetToAdd))
	{
		RegionChildren.Emplace(WidgetToAdd);
	}
}

void UUIRegionPanel::RemoveFromRegion(UUIDroppableBase* WidgetToRemove)
{
	if (!WidgetToRemove || !RegionPanel) return;

	if (RegionChildren.Contains(WidgetToRemove))
	{
		RegionChildren.Remove(WidgetToRemove);
	}
}




/*
								Accessors.
*/

UCanvasPanel* UUIRegionPanel::GetRegionPanel()
{
	return RegionPanel.Get();
}