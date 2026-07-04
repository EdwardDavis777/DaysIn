//Engine imports.
#include "UI/Player/Components/EquipSlotUIComponent.h"




//Component imports.
#include "Components/Image.h"
#include "Components/TextBlock.h" 
#include "Components/Border.h"
#include "Blueprint/DragDropOperation.h"


//Other imports.
#include "Items/Abstracts/ItemInstance.h"
#include "Items/Abstracts/ItemBase.h"



//Widget imports.
#include "UI/Player/UIEquipSlotBase.h"
#include "UI/Items/Abstracts/UIItemIconBase.h"
#include "UI/Interactables/Abstracts/UIDraggableBase.h"


//Utility imports.
#include "SubsystemUtilitys/SubsystemUtility.h"


//Subsystem imports.
#include "Subsystems/Save/SavePlayerEquipmentSubsystem.h"



void UEquipSlotUIComponent::Initialize(UWorld* WorldContext, UUserWidget* OwnerWidget)
{
	Super::Initialize(WorldContext, OwnerWidget);
	
	EquipSlot = FindOwner<UUIEquipSlotBase>();
	SaveEquipmentSubsystem = SubUtility::FindSub<USavePlayerEquipmentSubsystem>(WorldContext);
}




/*
							     Equipment slot event functions.
*/

void UEquipSlotUIComponent::HandleStore(UItemInstance* Instance, UUIItemIconBase* Icon, TObjectPtr<UItemInstance>& InstanceCache)
{
	if (!Instance || !Icon || !EquipSlot || !SaveEquipmentSubsystem) return;
    
	Icon->Init(Instance);
	InstanceCache = Instance;

	SaveEquipmentSubsystem->SaveEquipment(InstanceCache);
	CollapseDescription(Icon);
}



void UEquipSlotUIComponent::HandleRemove(TObjectPtr<UItemInstance>& AssocaitedInstance, TObjectPtr<UItemInstance>& InstanceCache, UUIItemIconBase* Icon)
{
	if (!AssocaitedInstance || !InstanceCache || !Icon) return;

	UnCollapseDescription(Icon);
   
	SaveEquipmentSubsystem->UnSaveEquipment(InstanceCache);
	InstanceCache = nullptr;
}



void UEquipSlotUIComponent::HandleHoverOver(UDragDropOperation* InOperation, const FLinearColor& CanPlaceColor)
{
	if (!InOperation || !InOperation->Payload || !EquipSlot) return;

	if (auto* Drag = Cast<UUIDraggableBase>(InOperation->Payload))
	{
		if (auto* Inst = Cast<UItemInstance>(Drag->GetAssocaitedInstance()))
		{
			if (bCanStore(Inst))
			{
				EquipSlot->GetBorder()->SetBrushColor(CanPlaceColor);
			}
		}
	}
}



void UEquipSlotUIComponent::ResetBorder(const FLinearColor& DefaultBorderColor)
{
	if (!EquipSlot) return;
	EquipSlot->GetBorder()->SetBrushColor(DefaultBorderColor);
}



void UEquipSlotUIComponent::CollapseDescription(UUIItemIconBase* Icon)
{
	if (!Icon || !EquipSlot) return;

	EquipSlot->GetDescription()->SetVisibility(ESlateVisibility::Collapsed);
	Icon->AddToRender();
}



void UEquipSlotUIComponent::UnCollapseDescription(UUIItemIconBase* Icon)
{
	if (!Icon) return;

	EquipSlot->GetDescription()->SetVisibility(ESlateVisibility::Visible);
	Icon->RemoveFromRender();
}



/*
									 Helper functions.
*/

bool UEquipSlotUIComponent::bCanStore(UItemInstance* ItemInstance)
{
	if (!ItemInstance || !EquipSlot) return false;

	if (EquipSlot->GetEquipTag() == ItemInstance->GetEquipTag() && !EquipSlot->IsOccupied())
	{
		return true;
	}
	return false;
}