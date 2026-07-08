#pragma once

/* 

    Defines class defaults for region panels, each region panel will
	define an editor defined region type. For each collectable storage
	type that defines a region type, it will store a matching region type
	with its own.

	Once instance is defined in the editor, then dragged into the UIPlayerMain widget
	UMG, then the region type is defined in there.

*/


//Other imports.
#include "SharedData/UI/UIRegionTag.h"


//Engine imports.
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIRegionPanel.generated.h"


//Forward declares.
class USizeBox;
class UCanvasPanel;
class UUIDroppableBase;


UCLASS()
class DAYSIN_API UUIRegionPanel : public UUserWidget
{
	GENERATED_BODY()
   
private:
	virtual void NativeConstruct() override;


	/*
	                         UUIRegionPanel components. 
	*/
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<USizeBox> RootSizeBox;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UCanvasPanel> RegionPanel;


	/*
	                                    Data.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data| Configurations", meta = (AllowPrivateAccess = true))
	ERegionTag RegionTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data| Runtime", meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<UUIDroppableBase>> RegionChildren;


public:

	/*
	                           Region event functions.
	*/

	/*
	      Adds a widget to this region panel
		  instance.

		  @param UUIDroppableBase: pointer to a widget you wish to 
		  add to this region panel.
	*/
	void AddToRegion(UUIDroppableBase* WidgetToAdd);


	/*
	      Removes a widget from this region panel
		  instance.

		  @parma UUIDroppableBase: pointer to a widget you wish to 
		  remove from this region panel.
	*/
	void RemoveFromRegion(UUIDroppableBase* WidgetToRemove);


	/*
	                                Accessors.
	*/
	FORCEINLINE const ERegionTag& GetRegionTag() const { return RegionTag; }
	UCanvasPanel* GetRegionPanel();
};