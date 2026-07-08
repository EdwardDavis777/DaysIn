//Engine imports.
#include "PlayerStorage/Components/CollectableStorageUIComponent.h"



//Component imports.
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"



//Other imports.
#include "PlayerStorage/Abstracts/CollectableStorageInstance.h"
#include "PlayerStorage/Data/CollectableStorageDataAsset.h"
#include "UI/Storages/Abstracts/UICollectableStorageInventory.h"
#include "UI/Player/UIPlayerMain.h"
#include "UI/Player/UIRegionPanel.h"



//Static data imports.
#include "StaticData/UI/WidgetMath.h"


//Utility imports.
#include "SubsystemUtilitys/SubsystemUtility.h"


//Subsystem imports.
#include "Subsystems/Player/PlayerUISubsystem.h"
#include "Subsystems/Player/PlayerEquipmentSubsystem.h"




void UCollectableStorageUIComponent::Initialize(UWorld* WorldContext, UObject* OwnerObject)
{
	Super::Initialize(WorldContext, OwnerObject);
	
	StorageInstance = GetOwner<UCollectableStorageInstance>();
	PlayerUISubsystem = SubUtility::FindSub<UPlayerUISubsystem>(WorldContext);
	PlayerEquipmentSubsystem = SubUtility::FindSub<UPlayerEquipmentSubsystem>(WorldContext);
	BindDelegates();
	
}

void UCollectableStorageUIComponent::BindDelegates()
{
	if (!PlayerEquipmentSubsystem) return;

	PlayerEquipmentSubsystem->PlayerEquipmentDispatches.StorageAdded.AddUObject(this, &UCollectableStorageUIComponent::CreateInventory);
	PlayerEquipmentSubsystem->PlayerEquipmentDispatches.StorageRemoved.AddUObject(this, &UCollectableStorageUIComponent::DeconstructInventory);
}





/*
								   Event functions.
*/

void UCollectableStorageUIComponent::CreateInventory(UCollectableStorageInstance* Instance)
{
	if (Instance != StorageInstance) return;

	if (!bAlreadyConstructed)
	{
		ConstructInitial(StorageInstance);
	}
	else
	{
		RebuildRegion();
	}
}

void UCollectableStorageUIComponent::DeconstructInventory(UCollectableStorageInstance* Instance)
{
	if (Instance != StorageInstance) return;

	ParentRegion->RemoveFromRegion(StorageInventory);
	StorageInventory->RemoveFromRender();
}



/*
								 Construction events.
*/
	

void UCollectableStorageUIComponent::ConstructInitial(UCollectableStorageInstance* Instance)
{
	if (!Instance || !PlayerUISubsystem || !StorageInstance) return;

	StorageInventory = CreateWidget<UUICollectableStorageInventory>(World, Instance->GetStaticStorageData()->CollectableStorageUIProperties.InventoryWidgetClass);
	if (!StorageInventory) return;

	ParentRegion = PlayerUISubsystem->GetPlayerMain()->AddToRegion(StorageInventory);
	if (!ParentRegion) return;

	ParentSlot = Cast<UCanvasPanelSlot>(ParentRegion->GetRegionPanel()->AddChild(StorageInventory));
	if (!ParentSlot) return;

	StorageInventory->InitializeGrid(StorageInstance->GetSize().X, StorageInstance->GetSize().Y, StorageInstance);
	SetRegionSize(StorageInstance);
	bAlreadyConstructed = true;

}



void UCollectableStorageUIComponent::RebuildRegion()
{
	if (!StorageInstance || !StorageInventory || !ParentRegion) return;

	ParentRegion->AddToRegion(StorageInventory);
	StorageInventory->AddToRender();
}




/*
								   Helper functions.
*/


void UCollectableStorageUIComponent::SetRegionSize(UCollectableStorageInstance* Instance)
{
	if (!Instance || !ParentSlot) return;

	const FVector2D& RegionSize = FVector2D(Instance->GetSize().X * WidgetMath::TileSize, Instance->GetSize().Y * WidgetMath::TileSize);
	ParentSlot->SetSize(RegionSize);
}