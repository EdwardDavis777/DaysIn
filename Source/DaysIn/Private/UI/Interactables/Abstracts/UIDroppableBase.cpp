//Engine imports.
#include "UI/Interactables/Abstracts/UIDroppableBase.h"


//Component imports.
#include "Blueprint/DragDropOperation.h"


 
//Custom component imports. 
#include "UI/Interactables/Components/DroppableUIComponent.h"
#include "CustomClasses/Components/Factory/NativeUITemplate.h"



//Other imports.
#include "UI/Interactables/Abstracts/UIDraggableBase.h"
#include "Items/Abstracts/ItemInstance.h"
#include "Items/Abstracts/ItemBase.h"



//Utility imports.
#include "SubsystemUtilitys/SubsystemUtility.h"
#include "SubsystemUtilitys/SubsystemUtility.h"

//Subsystem imports.
#include "Subsystems/UI/UIDraggableSubsystem.h"
#include "Subsystems/Player/PlayerUISubsystem.h"




void UUIDroppableBase::NativeConstruct()
{
	Super::NativeConstruct();

	DroppableComponent = NativeUITemplate::CreateDefaultUIComponent<UDroppableUIComponent>(GetWorld(), this);
	DraggableSubsystem = SubUtility::FindSub<UUIDraggableSubsystem>(GetWorld());
	PlayerUISubsystem = SubUtility::FindSub<UPlayerUISubsystem>(GetWorld());

	BindDelegates();
}


void UUIDroppableBase::BindDelegates()
{
	if (!DraggableSubsystem || !PlayerUISubsystem) return;
	DraggableSubsystem->DraggableDispatches.DragEventTriggered.AddUObject(this, &UUIDroppableBase::ProxyRemoveEvent);
	PlayerUISubsystem->PlayerUISubsystemDispatches.UIMainOutRender.AddUObject(this, &UUIDroppableBase::HookResetEvent);
}


/*
									Intermediate event functions.
*/

void UUIDroppableBase::ProxyRemoveEvent(TObjectPtr<UItemInstance>& AssociatedInstance)
{
	if (!AssociatedInstance) return;

	if (Data.StoredDragWidgets.Contains(AssociatedInstance))
	{
		RemoveStored(AssociatedInstance);
	}
}



/*
									   Virtual event functions.
*/

void UUIDroppableBase::StoreItem(AItemBase* Item)
{
	if (!Item) return;

	//Write these to construct a widget from the item instance.
	//Dynamically later.

}

bool UUIDroppableBase::StoreDropped(UItemInstance* ItemInstance)
{
	if (!ItemInstance) return false;

	//Write these to construct a widget from the item instance.
	//Dynamically later.
	return true;
}


void UUIDroppableBase::RemoveStored(TObjectPtr<UItemInstance>& AssociatedInstance)
{
	if (!AssociatedInstance) return;

	if (Data.StoredDragWidgets.Contains(AssociatedInstance))
	{
		Data.StoredDragWidgets.Remove(AssociatedInstance);
	}
}


/*
								    Virtual hook event functions.
*/

void UUIDroppableBase::HookDragOverEvent(UDragDropOperation* InOperation){}
void UUIDroppableBase::HookDragLeaveEvent(){}
void UUIDroppableBase::HookResetEvent(){}

/*
								  Engine UI input override functions.
*/

bool UUIDroppableBase::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDropEvent, UDragDropOperation* InOperation)
{
	if (!InOperation || !InOperation->Payload) return false;
	return DroppableComponent->HandleDrop(InOperation); 
}

bool UUIDroppableBase::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDropEvent, UDragDropOperation* InOperation)
{
	if (!InOperation || !InOperation->Payload) return false;
	
	HookDragOverEvent(InOperation);
	return true;
}

void UUIDroppableBase::NativeOnDragLeave(const FDragDropEvent& InDragEvent, UDragDropOperation* InOperation)
{
	HookDragLeaveEvent();
}


/*
										   Class mutators.
*/

void UUIDroppableBase::CacheExternalSourceWidget(TObjectPtr<UItemInstance>& AssocaitedInstance, UUIDraggableBase* DraggableWidget)
{
	if (!AssocaitedInstance || !DraggableWidget) return;

	if (!Data.StoredDragWidgets.Contains(AssocaitedInstance))
	{
		Data.StoredDragWidgets.Emplace(TObjectPtr<UItemInstance>(AssocaitedInstance), TObjectPtr<UUIDraggableBase>(DraggableWidget));
	}
}


/*
                                         Mutators.
*/

void UUIDroppableBase::AddToRender()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UUIDroppableBase::RemoveFromRender()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

/*
										Accessors.
*/

UBorder* UUIDroppableBase::GetBorder() const
{
	return MainBorder.Get();
}

USizeBox* UUIDroppableBase::GetSizeBox() const
{
	return RootSizeBox.Get();
}

const bool UUIDroppableBase::bIsVisible() const
{
	return GetVisibility() == ESlateVisibility::Visible;
}