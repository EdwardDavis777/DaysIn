//Engine imports.
#include "UI/Player/UIPlayerEquipmentMain.h"



void UUIPlayerEquipmentMain::NativeConstruct()
{
	Super::NativeConstruct();
}



/*
                                           Accessors.
*/

UCanvasPanel* UUIPlayerEquipmentMain::GetGroupPanel()
{
	return GroupPanel.Get();
}