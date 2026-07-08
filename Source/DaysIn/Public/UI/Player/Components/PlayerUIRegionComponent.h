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
class UUIDroppableBase;
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
	    Checks if the widget to add is assocaited with any regions in the UI player
		main, if so it will add it to the region cache.

		@param WidgetToAdd: pointer to a widget you wish 
		to add to a region.

		@return UUIRegionPanel: pointer to the region instance
		that added the passed widget.
	*/
	UUIRegionPanel* AddToRegion(UUIDroppableBase* WidgetToAdd);



private:

	/*
	                                  Components.
	*/
	UPROPERTY()
	TObjectPtr<UUIPlayerMain> PlayerMain;
};