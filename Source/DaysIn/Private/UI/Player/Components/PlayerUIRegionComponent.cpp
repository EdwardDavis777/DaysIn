//Engine imports.
#include "UI/Player/Components/PlayerUIRegionComponent.h"

//Component imports.
#include "Components/CanvasPanel.h"
#include "Components/SizeBox.h"



//Widget imports.
#include "UI/Player/UIPlayerMain.h"
#include "UI/Storages/Abstracts/UICollectableStorageInventory.h"
#include "UI/Player/UIRegionPanel.h"




void UPlayerUIRegionComponent::Initialize(UWorld* WorldContext, UUserWidget* OwningWidget)
{
	Super::Initialize(WorldContext, OwningWidget);
	PlayerMain = FindOwner<UUIPlayerMain>();
}



UUIRegionPanel* UPlayerUIRegionComponent::AddToRegion(UUIDroppableBase* WidgetToAdd)
{
	if (!WidgetToAdd || !PlayerMain) return nullptr;

	TArray<UWidget*> Children = PlayerMain->GetGroupPanel()->GetAllChildren();
	
	for (auto& Child : Children)
	{
		if (!Child) continue;

		if (auto* Region = Cast<UUIRegionPanel>(Child))
		{
			if (Region->GetRegionTag() == WidgetToAdd->GetRegionTag())
			{
				Region->AddToRegion(WidgetToAdd);
				return Region;
			}
		}
	}
	return nullptr;
}