//Engine imports
#include "UI/Interactables/Components/DroppableUIComponent.h"


//Component imports.
#include "Blueprint/DragDropOperation.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
 
//Widget imports.
#include "UI/Interactables/Abstracts/UIDroppableBase.h"
#include "UI/Interactables/Abstracts/UIDraggableBase.h"


//Other imports.
#include "Items/Abstracts/ItemInstance.h"
#include "Items/Abstracts/ItemBase.h"
#include "UI/Items/Abstracts/UIItemIconBase.h"


//Static data imports.
#include "StaticData/UI/WidgetMath.h"



void UDroppableUIComponent::Initialize(UWorld* WorldContext, UUserWidget* OwnerWidget)
{
	Super::Initialize(WorldContext, OwnerWidget);
	Droppable = FindOwner<UUIDroppableBase>();
}


/*
							        Droppable event functions.
*/

void UDroppableUIComponent::HandleStore(UItemInstance* Instance, TMap<TObjectPtr<UItemInstance>,TObjectPtr<UUIDraggableBase>>& StoredWidget,const FIntPoint& Position, UUIDroppableBase* EventOwner)
{
	if (!Instance || !EventOwner) return;

	auto* NewIcon = CreateWidget<UUIDraggableBase>(World, Instance->GetIconClass());
	if (NewIcon)
	{
		InitializeNewIcon(EventOwner->GetGroupPanel(), NewIcon,Instance,Position);
		StoredWidget.Emplace(TObjectPtr<UItemInstance>(Instance), TObjectPtr<UUIDraggableBase>(NewIcon));
	}
}


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



/*
								        Helper functions.
*/

void UDroppableUIComponent::InitializeNewIcon(UCanvasPanel* ParentPanel, UUIDraggableBase* NewIcon, UItemInstance* Instance, const FIntPoint& Position)
{
	if (!ParentPanel || !NewIcon || !Instance) return;

	if (auto* ParentSlot = Cast<UCanvasPanelSlot>(ParentPanel->AddChild(NewIcon)))
	{
		const FIntPoint IconSize = Instance->GetItemSize();
		FVector2D WidgetSize = FVector2D(WidgetMath::TileSize * IconSize.X, WidgetMath::TileSize * IconSize.Y);
		FVector2D IconPosition = FVector2D(WidgetMath::TileSize * Position.X, WidgetMath::TileSize * Position.Y);

		ParentSlot->SetSize(WidgetSize);
		ParentSlot->SetPosition(IconPosition);
		NewIcon->Init(Instance);
	}
}