//Engine imports.
#include "CustomClasses/Components/NativeUIComponent.h"



void UNativeUIComponent::Initialize(UWorld* WorldContext, UUserWidget* OwnerWidget)
{
	if (!WorldContext || !OwnerWidget) return;
	
	World = WorldContext;
	Owner = OwnerWidget;
}