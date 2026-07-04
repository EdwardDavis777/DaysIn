//Engine imports.
#include "UI/Interactables/Abstracts/UIDraggableBase.h"


//Component imports.
#include "Components/Border.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/SizeBox.h"



//Other imports.
#include "Items/Abstracts/ItemBase.h"


//Custom component imports.
#include "UI/Interactables/Components/DraggableUIComponent.h"
#include "CustomClasses/Components/Factory/NativeUITemplate.h"


//Utility imports.
#include "SubsystemUtilitys/SubsystemUtility.h"


//Subsystem imports.
#include "Subsystems/UI/UIDraggableSubsystem.h"
#include "Subsystems/Player/PlayerUISubsystem.h"




void UUIDraggableBase::NativeConstruct()
{
	Super::NativeConstruct();
	
	DraggableUIComponent = NativeUITemplate::CreateDefaultUIComponent<UDraggableUIComponent>(GetWorld(), this);
	DraggableSubsystem = SubUtility::FindSub<UUIDraggableSubsystem>(GetWorld());
	PlayerUISubsystem = SubUtility::FindSub<UPlayerUISubsystem>(GetWorld());

	if (MainBorder)
	{
		Data.ColorData.DefaultBorderColor = MainBorder->GetBrushColor();
	}
	BindDelegates();
}


void UUIDraggableBase::NativeDestruct()
{
	UnBindDelegates();
}

void UUIDraggableBase::BindDelegates()
{
	if (!PlayerUISubsystem) return;
	PlayerUISubsystem->PlayerUISubsystemDispatches.UIMainOutRender.AddUObject(this, &UUIDraggableBase::HookResetEvent);
}

void UUIDraggableBase::UnBindDelegates()
{
	if (!PlayerUISubsystem) return;
	PlayerUISubsystem->PlayerUISubsystemDispatches.UIMainOutRender.RemoveAll(this);
}


/*
								 Virtual construct functions.
*/

void UUIDraggableBase::Init(UItemInstance* Instance)
{
	if (!Instance) return;

	Data.RuntimeData.GeneralInstance = Instance;
	DraggableUIComponent->InitDefaults(this, Instance);
}

void UUIDraggableBase::Init(AItemBase* RawItem)
{
	if (!RawItem) return;

	Data.RuntimeData.GeneralInstance = RawItem->Instance();
	DraggableUIComponent->InitDefaults(this, RawItem->Instance());
}


/* 
							        Virtual hook functions.
*/

void UUIDraggableBase::HookDragEvent(){}
void UUIDraggableBase::HookMouseEnterEvent(){}
void UUIDraggableBase::HookMouseLeaveEvent(){}

void UUIDraggableBase::HookResetEvent()
{
	DraggableUIComponent->ResetDefaults(Data.ColorData.DefaultBorderColor);	
}


/*
							   Engine UI interact event functions.
*/

void UUIDraggableBase::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& InOperation)
{
	if (auto* DragOperation = NewObject<UDragDropOperation>())
	{
		DraggableUIComponent->MakeDragWidget(DragOperation, this, Data.RuntimeData.GeneralInstance);
		InOperation = DragOperation;

		HookDragEvent();
		DraggableSubsystem->DraggableDispatches.DragEventTriggered.Broadcast(Data.RuntimeData.GeneralInstance);
	}
}

void UUIDraggableBase::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (!InOperation || !InOperation->Payload) return;
	DraggableUIComponent->HandleDragCancelled(InOperation, PlayerUISubsystem);
}

void UUIDraggableBase::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	DraggableUIComponent->SetHoverGlow(Data.ColorData.HoverBorderColor);
	HookMouseEnterEvent(); 
}

void UUIDraggableBase::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	DraggableUIComponent->RemoveHoverGlow(Data.ColorData.DefaultBorderColor);
	HookMouseLeaveEvent();
}

FReply UUIDraggableBase::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}



/*
										 Mutators.
*/

void UUIDraggableBase::AddToRender()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UUIDraggableBase::RemoveFromRender()
{
	SetVisibility(ESlateVisibility::Collapsed);
}




/*
									      Accessors.
*/

USizeBox* UUIDraggableBase::GetSizeBox()
{
	return RootSizeBox;
}

const FVector2D UUIDraggableBase::GetSizeBoxSize() const
{
	if (!RootSizeBox) return FVector2D::ZeroVector;
	const FVector2D Size = FVector2D(RootSizeBox->GetWidthOverride(), RootSizeBox->GetHeightOverride());
	return Size;
}

TObjectPtr<UBorder> UUIDraggableBase::GetBorder()
{
	return MainBorder.Get();
}

TObjectPtr<UImage> UUIDraggableBase::GetImage()
{
	return DragIcon.Get();
}

const bool UUIDraggableBase::bVisible() const
{
	return GetVisibility() == ESlateVisibility::Visible;
}

UItemInstance* UUIDraggableBase::GetAssocaitedInstance() const
{
	return Data.RuntimeData.GeneralInstance.Get();
}

const FData& UUIDraggableBase::GetData() const
{
	return Data;
}