//Engine imports
#include "UI/Interactables/Components/DroppableUIComponent.h"


//Component imports.
#include "Blueprint/DragDropOperation.h"



//Widget imports.
#include "UI/Interactables/Abstracts/UIDroppableBase.h"
#include "UI/Interactables/Abstracts/UIDraggableBase.h"


//Other imports.
#include "Items/Abstracts/ItemInstance.h"
#include "Items/Abstracts/ItemBase.h"




void UDroppableUIComponent::Initialize(UWorld* WorldContext, UUserWidget* OwnerWidget)
{
	Super::Initialize(WorldContext, OwnerWidget);
	Droppable = FindOwner<UUIDroppableBase>();
}


/*
							      Droppable event functions.
*/

bool UDroppableUIComponent::HandleDrop(UDragDropOperation* InOperation)
{
	if (!InOperation || !InOperation->Payload || !Droppable) return false;

	if (auto* DragWidget = Cast<UUIDraggableBase>(InOperation->Payload))
	{
		if (auto* DragInst = Cast<UItemInstance>(DragWidget->GetAssocaitedInstance()))
		{
			Droppable->StoreDropped(DragInst);
			return true;
		}
	}
	return false;
}