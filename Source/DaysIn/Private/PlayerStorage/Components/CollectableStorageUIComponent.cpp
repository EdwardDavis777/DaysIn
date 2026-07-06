//Engine imports.
#include "PlayerStorage/Components/CollectableStorageUIComponent.h"



//Component imports.
#include "Blueprint/UserWidget.h"
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




void UCollectableStorageUIComponent::Initialize(UWorld* WorldContext, UObject* OwnerObject)
{
	Super::Initialize(WorldContext, OwnerObject);
	
	CollectableStorageInstance = GetOwner<UCollectableStorageInstance>();
	PlayerUISubsystem = SubUtility::FindSub<UPlayerUISubsystem>(WorldContext);
}






/*
						     Widget construction event functions.
*/

void UCollectableStorageUIComponent::MakeInventory(const int32& Columns,const int32& Rows)
{
	if (!CollectableStorageInstance || !PlayerUISubsystem) return;

	if (!bAlreadyConstructed)
	{
		ConstructInitial(Columns, Rows);
	}
	else
	{
		RebuildInRegion();
	}
}

void UCollectableStorageUIComponent::ConstructInitial(const int32& Columns, const int32& Rows)
{
	if (!CollectableStorageInstance || !PlayerUISubsystem) return;

	if (InventoryWidget = CreateWidget<UUICollectableStorageInventory>(World, CollectableStorageInstance->GetInventoryClass()))
	{
		ParentPanel = PlayerUISubsystem->GetPlayerMain()->AddToRegion(InventoryWidget);
		if (!ParentPanel) return;

		InventoryWidget->InitializeGrid(Columns, Rows);
		SetRegionPanelSize(ParentPanel, Columns, Rows);
		bAlreadyConstructed = true;
	}
}

void UCollectableStorageUIComponent::RebuildInRegion()
{
	if (!InventoryWidget || !ParentPanel) return;

	ParentPanel->GetSizeBox()->AddChild(InventoryWidget);
	SetRegionPanelSize(ParentPanel, CollectableStorageInstance->GetStaticStorageData()->CollectableStorageProperties.StorageSize.X, CollectableStorageInstance->GetStaticStorageData()->CollectableStorageProperties.StorageSize.Y);
	InventoryWidget->AddToRender();
}





/*
							  Widget deconstruction event functions.
*/

void UCollectableStorageUIComponent::ClearInventory()
{
	if (!InventoryWidget || !ParentPanel) return;

	ParentPanel->RemoveChildFromRegion(InventoryWidget);
	InventoryWidget->RemoveFromRender();
}




/*
                                        Helper functions.
*/

void UCollectableStorageUIComponent::SetRegionPanelSize(UUIRegionPanel* RegionPanel, const int32& Columns, const int32& Rows)
{
	if (!RegionPanel || !InventoryWidget) return; 

	if (auto* RegionSlot = Cast<UCanvasPanelSlot>(RegionPanel->Slot))
	{
		FIntPoint SlotSize = FIntPoint{ Columns * WidgetMath::TileSize,Rows * WidgetMath::TileSize };
		RegionSlot->SetSize(SlotSize);
	}
}


/*
										  Accessors.
*/

UUICollectableStorageInventory* UCollectableStorageUIComponent::GetInventoryWidget()
{
	return InventoryWidget.Get();
}