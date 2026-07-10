//Engine imports.
#include "Items/Components/InstanceUIRuntimeComponent.h"

//Other imports.
#include "Items/Abstracts/ItemInstance.h"


//Utility imports.
#include "SubsystemUtilitys/SubsystemUtility.h"


//Subsystem imports.
#include "Subsystems/UI/UISubsystem.h"
#include "Subsystems/Item/ItemEventSubsystem.h"



void UInstanceUIRuntimeComponent::Initialize(UWorld* WorldContext, UObject* OwnerObject)
{
	Super::Initialize(WorldContext, OwnerObject);

	ItemInstance = GetOwner<UItemInstance>();
	UISubsystem = SubUtility::FindSub<UUISubsystem>(WorldContext);
	ItemEventSubsystem = SubUtility::FindSub<UItemEventSubsystem>(WorldContext);
	BindDelegates();
}

void UInstanceUIRuntimeComponent::BindDelegates()
{
	if (!ItemEventSubsystem) return;
	ItemEventSubsystem->Dispatches.ItemDropped.AddUObject(this, &UInstanceUIRuntimeComponent::ResetRotated);
}




/*
						         Item instance UI event functions.
*/

void UInstanceUIRuntimeComponent::NotifyRotated(UItemInstance* RotatedInstance, UUIDraggableBase* AssocaitedWidget)
{
	if (!RotatedInstance || !AssocaitedWidget || !UISubsystem) return;

	auto& UIData = RotatedInstance->GetItemRuntimeData().ItemUIRuntimeData;
	auto ItemSize = RotatedInstance->GetItemSize();
	
	if (!UIData.bItemRotated)
	{
		UIData.RotatedSize = FIntPoint(ItemSize.Y, ItemSize.X);
		UIData.bItemRotated = true;
		UISubsystem->UISubsystemDispatches.ForwardRotatedItem.Broadcast(RotatedInstance, AssocaitedWidget, true);
	    
		return;
	}
	UIData.bItemRotated = false;
	UISubsystem->UISubsystemDispatches.ForwardRotatedItem.Broadcast(RotatedInstance, AssocaitedWidget, false);
}

void UInstanceUIRuntimeComponent::ResetRotated(UItemInstance* RotatedInstance)
{
	if (!RotatedInstance) return;

	auto& UIData = RotatedInstance->GetItemRuntimeData().ItemUIRuntimeData;
	if (UIData.bItemRotated)
	{
		UIData.bItemRotated = false;
	}
}