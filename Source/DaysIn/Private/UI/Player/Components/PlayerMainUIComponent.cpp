//Engine imports.
#include "UI/Player/Components/PlayerMainUIComponent.h"


//Component imports.
#include "Framework/Application/SlateApplication.h"


//Widget imports.
#include "UI/Player/UIPlayerMain.h"
#include "UI/Player/UIPlayerEquipmentMain.h" 
#include "UI/Interactables/Abstracts/UIDraggableBase.h"


//Other imports.
#include "Items/Abstracts/ItemInstance.h"
#include "Items/Abstracts/ItemBase.h"
#include "Characters/Player/Survivor.h"
#include "UI/Interactables/Abstracts/GlobalEvents/DraggableTemplates/DraggableTemplates.h"

//Utility imports.
#include "SubsystemUtilitys/SubsystemUtility.h"


//Subsystem imports.
#include "Subsystems/Player/PlayerUISubsystem.h"
#include "Subsystems/Player/PlayerSubsystem.h"





void UPlayerMainUIComponent::Initialize(UWorld* WorldContext, UUserWidget* OwnerWidget)
{
	Super::Initialize(WorldContext, OwnerWidget);
	
	PlayerMain = FindOwner<UUIPlayerMain>();
	PlayerUISubsystem = SubUtility::FindSub<UPlayerUISubsystem>(WorldContext);
	PlayerSubsystem = SubUtility::FindSub<UPlayerSubsystem>(WorldContext);
	BindDelegates();
}


void UPlayerMainUIComponent::BindDelegates()
{
	if (!PlayerUISubsystem) return;

	PlayerUISubsystem->PlayerUISubsystemDispatches.UIMainOutRender.AddUObject(this, &UPlayerMainUIComponent::CancelDragEvents);
	PlayerUISubsystem->PlayerUISubsystemDispatches.ForceSpawnActor.AddUObject(this, &UPlayerMainUIComponent::ForceSpawnEvent);
	
}



/*
							          Event functions.
*/


void UPlayerMainUIComponent::UpdateUISubsystem()
{ 
	if (!PlayerMain || !PlayerMain->GetPlayerEquipmentMain() || !PlayerUISubsystem) return;
	
	PlayerUISubsystem->SetPlayerMain(PlayerMain);
	PlayerUISubsystem->SetPlayerEquipmentMain(PlayerMain->GetPlayerEquipmentMain());
}


void UPlayerMainUIComponent::CancelDragEvents()
{
	if (FSlateApplication::IsInitialized() && FSlateApplication::Get().IsDragDropping())
	{
		FSlateApplication::Get().CancelDragDrop();
	}
}


/*
							       Spawn event functions.
*/



bool UPlayerMainUIComponent::SpawnEvent(UDragDropOperation* InOperation)
{
	if (!InOperation || !InOperation->Payload) return false;

	if (UItemInstance* DropInst = DraggableTemplate::GetPayloadInstance<UUIDraggableBase>(InOperation))
	{
		SpawnItem(DropInst);
		return true;
	}
	return false;
}



void UPlayerMainUIComponent::ForceSpawnEvent(UItemInstance* ItemInstance)
{
	if (!ItemInstance) return;
	SpawnItem(ItemInstance);
}



void UPlayerMainUIComponent::SpawnItem(UItemInstance* ItemInstance)
{
	if (!ItemInstance || !PlayerSubsystem || !World) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FVector PlayerLoc = PlayerSubsystem->GetPlayer()->GetActorLocation() + PlayerSubsystem->GetPlayer()->GetActorForwardVector() * 200.0f;
	FRotator SpawnRot = FRotator::ZeroRotator;

	if (auto* NewItem = World->SpawnActor<AItemBase>(ItemInstance->GetItemClass(), PlayerLoc, SpawnRot, SpawnParams))
	{
		NewItem->Drop(ItemInstance);
	}
}