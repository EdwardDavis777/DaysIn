#pragma once

/*
     Main player widget window, responsable for holding all default player
	 inventory related widgets. 
*/


//Engine imports.
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIPlayerMain.generated.h" 
 
  

 
//Forward declares.
class UCanvasPanel;
class UBorder;
class UBackgroundBlur;

class UUIPlayerEquipmentMain;
class UPlayerMainUIComponent;
class UUIRegionPanel;
class UPlayerUIRegionComponent;
class UUICollectableStorageInventory;



UCLASS()
class DAYSIN_API UUIPlayerMain : public UUserWidget
{
	GENERATED_BODY()


private:
	virtual void NativeConstruct() override;


	/*
	                             UUIPlayerMain components.
	*/
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UCanvasPanel> RootPanel;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UBorder> MainBorder;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UCanvasPanel> GroupPanel;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UBackgroundBlur> BackgroundBlur;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UUIPlayerEquipmentMain> UIPlayerEquipmentMain;





    /*
	                                  Region components.
	*/
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UUIRegionPanel> BackpackRegion;






	/*
	                                  Custom components.
	*/
	UPROPERTY(VisibleAnywhere, Category = "Data|Memory", meta = (AllowPrivateAccess = true))
	TObjectPtr<UPlayerMainUIComponent> PlayerMainUIComponent;

	UPROPERTY(VisibleAnywhere, Category = "Data|Memory", meta = (AllowPrivateAccess = true))
	TObjectPtr<UPlayerUIRegionComponent> PlayerUIRegionComponent;


	/*
	                                  Cache components.
	*/
	UPROPERTY(VisibleAnywhere, Category = "Data|Memory", meta = (AllowPrivateAccess = true))
	TObjectPtr<APlayerController> OwnerController;



	/*
	                              Engine UI input overrides.
	*/
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDropEvent, UDragDropOperation* InOperation) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
public:

	/*
	                            Construction event functions.
	*/
    
	/*
	     Finishes the construction of a UIPlayerMain instance, adds itself to the 
		 view-port and sets its visibility to collapsed.

		 @param PlayerController: pointer to the controller instance 
		 you wish to own this widget instance.
	*/
	void FinishConstruction(APlayerController* PlayerController);


	/*
	                                Add event functions.
	*/

	/*
	     Adds some inventory instance to a region defined inside of this
		 widgets group panel.

		 @param InventoryInstance: pointer some external inventory
		 instance you wish to add to this widgets region tree.

		 @return UUIRegionPanel: pointer to the assocaited region panel
		 the instance was added into to the caller.
	*/
	UUIRegionPanel* AddToRegion(UUICollectableStorageInventory* InventoryInstance);


	/*
	                                 Render Mutators.
	*/
	void AddToRender();
	void RemoveFromRender();
	
	/*
	                                  Input mutators.
	*/
	void AddCursorInput();
	void RemoveCursorInput();



	/*
	                                    Accessors.
	*/
	bool bIsVisible();
	UUIPlayerEquipmentMain* GetPlayerEquipmentMain();
};