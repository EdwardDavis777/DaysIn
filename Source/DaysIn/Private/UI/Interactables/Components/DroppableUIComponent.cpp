//Engine imports
#include "UI/Interactables/Components/DroppableUIComponent.h"


//Component imports.
#include "Blueprint/DragDropOperation.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h" 

//Widget imports.
#include "UI/Interactables/Abstracts/UIDroppableBase.h"
#include "UI/Interactables/Abstracts/UIDraggableBase.h"


//Other imports.
#include "Items/Abstracts/ItemInstance.h"
#include "Items/Abstracts/ItemBase.h"
#include "UI/Items/Abstracts/UIItemIconBase.h"
#include "UI/Interactables/Abstracts/GlobalEvents/DraggableTemplates/DraggableTemplates.h"
#include "UI/GlobalActions/TransformAction.h"

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
		InitializeNewIcon(EventOwner->GetGroupPanel(), NewIcon, Instance, Position);
		StoredWidget.Emplace(TObjectPtr<UItemInstance>(Instance), TObjectPtr<UUIDraggableBase>(NewIcon));
	}
}



bool UDroppableUIComponent::HandleDrop(UDragDropOperation* InOperation)
{
	if (!InOperation || !InOperation->Payload || !Droppable) return false;

	if (UItemInstance* ItemInstance = DraggableTemplate::GetPayloadInstance<UUIDraggableBase>(InOperation))
	{
		Droppable->StoreDropped(ItemInstance);
		return true;
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
		const FIntPoint DynamicSize = Instance->GetDynamicUISize();

		FVector2D WidgetSize = FVector2D(WidgetMath::TileSize * DynamicSize.X, WidgetMath::TileSize * DynamicSize.Y);
		FVector2D IconPosition = FVector2D(WidgetMath::TileSize * Position.X, WidgetMath::TileSize * Position.Y);

		ParentSlot->SetSize(WidgetSize);
		ParentSlot->SetPosition(IconPosition);
		NewIcon->Init(Instance);
		if (Instance->bRotated()) { Transform::Rot::RotNeg90(NewIcon->GetDragIcon()); }
	}
}