#pragma once

/*

    Defines class defaults for region panels, each region panel will
	define an editor defined region type. For each collectable storage
	type that defines a region type, it will store a matching region type
	with its own.

	Once instance is defined in the editor, then dragged into the UIPlayerMain widget
	UMG, then the region type is defined in there.

	Note: this class provides a get child widget member function, kinda strange looking 
	but it caches an array of UWidget pointers then returns a pointer to the first 
	element in the array, this is done as each region is meant to hold only one child.
	Would be strange to make callers manually use only the first index, but this is really
	the only way as unreal's accessor expects an array of possible children.

*/


//Other imports.
#include "SharedData/UI/UIRegionTag.h"


//Engine imports.
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIRegionPanel.generated.h"


//Forward declares.
class USizeBox;



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


	/*
	                                    Data.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data| Configurations", meta = (AllowPrivateAccess = true))
	ERegionTag RegionTag;


public:

	/*
	                                Log methods.
	*/

	/*
	      Simply caches all children into an array, and prints
		  the amount of children in that array.

		  @param logTime: time in seconds you wish the log to 
		  be printed on the screen, defaulted to just 10 seconds.

		  @return int32(): the number of children inside of this 
		  current region panel.
	*/
	int32 LogRegionChildren(double logTime = 10.0f);
	

	/*
	                                 Mutators.
	*/

	/*
	     Removes a user widget from this region panel.

		 @param WidgetToRemove: pointer to the widget
		 you wish to remove from this region.
	*/
	void RemoveChildFromRegion(UUserWidget* WidgetToRemove);


	/*
	                                Accessors.
	*/
	FORCEINLINE const ERegionTag& GetRegionTag() const { return RegionTag; }
	
	UWidget* GetChild();
	USizeBox* GetSizeBox();
};