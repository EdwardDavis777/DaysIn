//Engine imports.
#include "UI/Player/UIPlayerMain.h"

//Component imports.
#include "Blueprint/DragDropOperation.h"


//Custom component imports.
#include "UI/Player/Components/PlayerMainUIComponent.h"
#include "UI/Player/Components/PlayerUIRegionComponent.h" 
#include "CustomClasses/Components/Factory/NativeUITemplate.h"


  
void UUIPlayerMain::NativeConstruct()
{ 
	Super::NativeConstruct(); 
	
	if (PlayerMainUIComponent = NativeUITemplate::CreateDefaultUIComponent<UPlayerMainUIComponent>(GetWorld(), this))
	{
		PlayerMainUIComponent->UpdateUISubsystem();
	}
	PlayerUIRegionComponent = NativeUITemplate::CreateDefaultUIComponent<UPlayerUIRegionComponent>(GetWorld(), this);

}


 
/*
							  	 Construction event functions.
*/

void UUIPlayerMain::FinishConstruction(APlayerController* PlayerController)
{
	if (!PlayerController) return;

	AddToViewport();
	SetOwningPlayer(PlayerController);
	RemoveFromRender();
	OwnerController = PlayerController;
}


/*
									 Add event functions.
*/

UUIRegionPanel* UUIPlayerMain::AddToRegion(UUICollectableStorageInventory* InventoryInstance)
{
	if (!InventoryInstance || !GroupPanel) return nullptr;
	return PlayerUIRegionComponent->AddWidgetToRegion(InventoryInstance, GroupPanel);
}



/*
								  Engine UI input overrides.
*/

bool UUIPlayerMain::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDropEvent, UDragDropOperation* InOperation)
{
	if (!InOperation || !InOperation->Payload) return false;
	return PlayerMainUIComponent->SpawnEvent(InOperation);
}

FReply UUIPlayerMain::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return FReply::Handled();
}







/*
								     Render Mutators.
*/

void UUIPlayerMain::AddToRender()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UUIPlayerMain::RemoveFromRender()
{
	SetVisibility(ESlateVisibility::Collapsed);
}


/*
									 Input mutators.
*/

void UUIPlayerMain::AddCursorInput()
{
	if (!OwnerController) return;

	OwnerController->SetInputMode(FInputModeGameAndUI());
	OwnerController->SetShowMouseCursor(true);
}

void UUIPlayerMain::RemoveCursorInput()
{
	if (!OwnerController) return;

	OwnerController->SetInputMode(FInputModeGameOnly());
	OwnerController->SetShowMouseCursor(false);
}




/*
									  Accessors.
*/

bool UUIPlayerMain::bIsVisible()
{
	return GetVisibility() == ESlateVisibility::Visible;
}

UUIPlayerEquipmentMain* UUIPlayerMain::GetPlayerEquipmentMain()
{
	return UIPlayerEquipmentMain.Get();
}