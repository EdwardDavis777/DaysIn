//Engine imports.
#include "UI/Interactables/Components/DraggableUIComponent.h"


//Component imports.
#include "Blueprint/DragDropOperation.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"



//Other imports.
#include "Items/Abstracts/ItemInstance.h"



//Static data imports.
#include "StaticData/UI/WidgetMath.h"


//Widget imports.
#include "UI/Interactables/Abstracts/UIDraggableBase.h"


//Subsystem imports.
#include "Subsystems/Player/PlayerUISubsystem.h"



void UDraggableUIComponent::Initialize(UWorld* WorldContext, UUserWidget* OwnerWidget)
{
	Super::Initialize(WorldContext, OwnerWidget);
	DraggableWidget = FindOwner<UUIDraggableBase>();
}




/*
								   Draggable event functions.
*/

void UDraggableUIComponent::InitDefaults(UUIDraggableBase* DragInstance, UItemInstance* Instance)
{
	if (!DragInstance || !Instance) return;
	DragInstance->GetImage()->SetBrushFromTexture(Instance->GetItemIcon());
}


void UDraggableUIComponent::MakeDragWidget(UDragDropOperation* InOperation,UUIDraggableBase* EventOwner, TObjectPtr<UItemInstance>& OwnerInstance)
{
	if (!InOperation || !EventOwner || !OwnerInstance) return;
     
	if (auto* Drag = CreateWidget<UUIDraggableBase>(World, OwnerInstance->GetIconClass()))
	{
		CopyDefaults(EventOwner, Drag, OwnerInstance);
		SetDragWidgetSize(Drag, OwnerInstance);
		InOperation->DefaultDragVisual = Drag;
		InOperation->Payload = Drag;
		InOperation->Pivot = EDragPivot::CenterCenter;
		InOperation->Offset = FVector2D::ZeroVector;
	}
}

void UDraggableUIComponent::HandleDragCancelled(UDragDropOperation* InOperation, UPlayerUISubsystem* PlayerUISubsystem)
{
	if (!InOperation || !PlayerUISubsystem) return;

	if (auto* Drag = Cast<UUIDraggableBase>(InOperation->Payload))
	{
		if (auto* DragInst = Cast<UItemInstance>(Drag->GetAssocaitedInstance()))
		{
			PlayerUISubsystem->PlayerUISubsystemDispatches.ForceSpawnActor.Broadcast(DragInst);
		}
	}
}


void UDraggableUIComponent::SetHoverGlow(const FLinearColor& HoverColor)
{
	if (!DraggableWidget) return;
	DraggableWidget->GetBorder()->SetBrushColor(HoverColor);
}


void UDraggableUIComponent::RemoveHoverGlow(const FLinearColor& DefaultBorderColor)
{
	if (!DraggableWidget) return;
	DraggableWidget->GetBorder()->SetBrushColor(DefaultBorderColor);
}


void UDraggableUIComponent::ResetDefaults(const FLinearColor& DefaultBorderColor)
{
	if (!DraggableWidget) return;
	DraggableWidget->GetBorder()->SetBrushColor(DefaultBorderColor);
}


/*
									   Helper functions.
*/


void UDraggableUIComponent::SetDragWidgetSize(UUIDraggableBase* DragWidget, TObjectPtr<UItemInstance>& Instance)
{
  	if (!DragWidget || !Instance || !DragWidget->GetSizeBox()) return;
   
	FVector2D NewSize = FVector2D(WidgetMath::TileSize * Instance->GetItemSize().X, WidgetMath::TileSize * Instance->GetItemSize().Y);
	DragWidget->GetSizeBox()->SetWidthOverride(NewSize.X);
	DragWidget->GetSizeBox()->SetHeightOverride(NewSize.Y);
}


void UDraggableUIComponent::CopyDefaults(UUIDraggableBase* Reference, UUIDraggableBase* Copy, TObjectPtr<UItemInstance>& OwnerInstance)
{
	if (!Reference || !Copy || !OwnerInstance) return;

	Copy->GetBorder()->SetBrushColor(Reference->ColorData.DragBorderColor);
	Copy->GetImage()->SetBrush(Reference->GetImage()->GetBrush());
	Copy->Init(OwnerInstance);
}