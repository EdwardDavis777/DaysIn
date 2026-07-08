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

void UUIDroppableBase::NativeDestruct()
{
	Super::NativeDestruct();
	UnBindDelegates();
}


void UUIDroppableBase::BindDelegates()
{
	if (!DraggableSubsystem || !PlayerUISubsystem) return;
	
	DraggableSubsystem->DraggableDispatches.DragEventTriggered.AddUObject(this, &UUIDroppableBase::ProxyRemoveEvent);
	PlayerUISubsystem->PlayerUISubsystemDispatches.UIMainOutRender.AddUObject(this, &UUIDroppableBase::HookResetEvent);
}

void UUIDroppableBase::UnBindDelegates()
{
	if (!DraggableSubsystem || !PlayerUISubsystem) return;

	DraggableSubsystem->DraggableDispatches.DragEventTriggered.RemoveAll(this);
	PlayerUISubsystem->PlayerUISubsystemDispatches.UIMainOutRender.RemoveAll(this);
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

void UUIDroppableBase::StoreItem(AItemBase* Item, const FIntPoint& Position)
{ if (!Item) return; }


void UUIDroppableBase::StoreItem(UItemInstance* Instance, const FIntPoint& Position)
{
	if (!Instance || !DroppableComponent) return;
	DroppableComponent->HandleStore(Instance, Data.StoredDragWidgets, Position, this);
}


bool UUIDroppableBase::StoreDropped(UItemInstance* ItemInstance, const FIntPoint& Position)
{
	if (!ItemInstance) return false;
	
	DroppableComponent->HandleStore(ItemInstance, Data.StoredDragWidgets, Position, this);
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

void UUIDroppableBase::HookDragOverEvent(const FGeometry& InGeometry, const FDragDropEvent& InDragEvent, UDragDropOperation* InOperation){}
void UUIDroppableBase::HookDragLeaveEvent(const FDragDropEvent& InDragEvent, UDragDropOperation* InOperation){}
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
	HookDragOverEvent(InGeometry,InDropEvent,InOperation);

	return true;
}

void UUIDroppableBase::NativeOnDragLeave(const FDragDropEvent& InDragEvent, UDragDropOperation* InOperation)
{
	HookDragLeaveEvent(InDragEvent,InOperation);
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

UCanvasPanel* UUIDroppableBase::GetGroupPanel() const
{
	return GroupPanel.Get();
}

UUIDraggableBase* UUIDroppableBase::FindStoredWidget(UItemInstance* AssocaitedInstance) const
{
	if (!AssocaitedInstance) return nullptr;

	if (auto* FoundWidget = Data.StoredDragWidgets.Find(AssocaitedInstance))
	{
		return *FoundWidget;
	}
	return nullptr;
}

const bool UUIDroppableBase::bIsVisible() const
{
	return GetVisibility() == ESlateVisibility::Visible;
}