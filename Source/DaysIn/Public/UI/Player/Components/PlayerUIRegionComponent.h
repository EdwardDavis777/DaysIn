#pragma once

/*

     Handles adding widgets into the UI player main that is added using the
	 region layout.

*/


//Engine imports.
#include "CoreMinimal.h"
#include "CustomClasses/Components/NativeUIComponent.h"
#include "PlayerUIRegionComponent.generated.h"



//Forward declares.
class UUIPlayerMain;
class UUICollectableStorageInventory;
class UCanvasPanel;
class UUIRegionPanel;



UCLASS()
class DAYSIN_API UPlayerUIRegionComponent : public UNativeUIComponent
{
	GENERATED_BODY()
   
public:
	virtual void Initialize(UWorld* WorldContext, UUserWidget* OwningWidget) override;


	/*
	                               Region event functions.
	*/

	/*
	     Adds a storage instance's inventory to its assocaited region type
		 in the player mains group panel.

		 @param InventoryInstance: pointer to some storage inventory 
		 instance.

		 @param GroupPanel: pointer to the UI player mains
		 group canvas panel.

		 @return UUIRegionPanel: pointer to the region panel that the assocaited inventory
		 instance was added to.
	*/
	UUIRegionPanel* AddWidgetToRegion(UUICollectableStorageInventory* InventoryInstance,UCanvasPanel* GroupPanel);

private:

	/*
	                                  Components.
	*/
	UPROPERTY()
	TObjectPtr<UUIPlayerMain> PlayerMain;
};