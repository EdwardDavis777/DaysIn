#pragma once


/*

     Defines class defaults for widget instances that need drop logic
	 implemented into them for item instances etc.

	 All widgets that implement really any sort of dropping logic
	 are derived from this class, such as inventory grids, equipment 
	 slots, storages etc. 
	  
*/ 


//Other imports.
#include "UI/Interactables/AbstractData/UIDroppableData.h"
#include "SharedData/UI/UIRegionTag.h"

//Engine imports.
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIDroppableBase.generated.h"



//Forward declares.
class USizeBox;
class UBorder;
class UCanvasPanel;
class UDroppableUIComponent;
class UUISubsystem;
class UPlayerUISubsystem;
class UItemInstance;
class AItemBase;



UCLASS(Abstract)
class DAYSIN_API UUIDroppableBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void BindDelegates();
	void UnBindDelegates();
	
	/*
	                               UUIDroppableBase components.
	*/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> RootSizeBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> MainBorder;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> GroupPanel;


	/*
	                                         Data.
	*/
	UPROPERTY(VisibleAnywhere, Category = "Data|Memory")
	FDroppableRuntimeData Data;
	
	UPROPERTY(EditAnywhere, Category = "Data|Configurations")
	ERegionTag RegionTag;


	/*
	                                    Custom components.
	*/
	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<UDroppableUIComponent> DroppableComponent;


	/*
	                                     Cache components.
	*/
	UPROPERTY()
	TObjectPtr<UUISubsystem> UISubsystem;

	UPROPERTY()
	TObjectPtr<UPlayerUISubsystem> PlayerUISubsystem;



	/*
	                                       Class mutators.
	*/

	/*
	     Allows classes to cache draggable widget manually, or through an external source; allows
		 classes to bypass manual widget construct if they wish to track widgets that have 
		 been constructed from some sort of outside source. Also allows tracking from this class 
		 for static instances of draggable widgets. 

		 @param AssocaitedInstance: pointer to an item instance you wish to assocaite
		 to the draggable widget.

		 @param DraggableWidget: pointer to the draggable widget you 
		 wish to track.
	*/
	void CacheExternalSourceWidget(TObjectPtr<UItemInstance>& AssocaitedInstance, UUIDraggableBase* DraggableWidget);

private:

	/*
								   Intermediate event functions.
	*/

	/*
	
	     Performs a simple cache check; ensures that the passed assocaited instance
		 is actually assocaited/stored inside of this droppable widget instance. Then 
		 calls the RemoveStored function if and only if the check is true.

		 Note: this function is binded to a dispatch that triggers when a stored draggable
		 widget is dragged.

		 @param InDragOperation: pointer to the current
		 drag and drop operation.
	*/
	void ProxyRemoveEvent(UDragDropOperation* InDragOperation);



	/*
	                              Engine UI input override functions.
	*/
 	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragEvent, UDragDropOperation* InOperation) override;
    
public:

	/*
	                                   Virtual event functions.
	*/
	

	/*
	    Handles the construction of a draggable widget through a raw item
	    pointer.

	    @param Item: pointer to a raw item pickedup
	    from the world.

		@param Position: refrence to the 2D position 
		to store the item at. Defaulted to zero for 
		droppables that do not implement dynamic positioning.
    */
	virtual void StoreItem(AItemBase* Item,const FIntPoint& Position = FIntPoint(0,0));

	
	/*
	     Handles the constructin of a draggable widget through an item instance
		 pointer.

		@param Instance: pointer to an item instance pickedup
		from the world.

		@param Position: refrence to the 2D position
		to store the item at. Defaulted to zero for
		droppables that do not implement dynamic positioning.
	*/
	virtual void StoreItem(UItemInstance* Instance, const FIntPoint& Position = FIntPoint(0, 0));




	/*
	    Handles storing during drop events for draggable widgets through an 
		instance pointer.

		@param ItemInstance: pointer to an item instance
		you wish to store.

		@param Position: reference to the current drop position
		in screen space. Defaulted to 0,0 in case you wish to use some
		other way.


		@return TRUE/FLASE: true if the dropped item was stored,
		false if the dropped item faild for some reason.
	*/
	virtual bool StoreDropped(UItemInstance* ItemInstance,const FIntPoint& Position = FIntPoint(0,0));



	/*
	    Removes a stored widget from this widgets storage cache. This
		function is only called if and only if the assocaited droppable instance is 
		actually storing this assocaited instance. The function is called during an 
		intermediate dispatch event.

		@param AssocaitedInstance: pointer to an item instance that is assocaited
		with a stored draggable widget.
	*/
	virtual void RemoveStored(TObjectPtr<UItemInstance>& AssocaitedInstance);




	/*
	                               Virtual hook event functions.
	*/

	/*
	    Allows derived classes to hook into drag over events from
		the parent. Simply override and implment logic you wish 
		to happen during drag over events.

		@param InGeometry: reference to the cached geometry
		during the drag event.

		@param InDragEvent: reference to the drag event struct
		data.

		@param InOperation: pointer to the current drag 
		drop operation.
	*/
	virtual void HookDragOverEvent(const FGeometry& InGeometry,const FDragDropEvent& InDragEvent,UDragDropOperation* InOperation);


	/*
	    Allows derived classes to hook into drag leave events from
		the parent. Simply override and implement logic you wish to
		happen during a drag leave event.

		@param InDragEvent: reference to the drag event 
		struct data.

		@param InOperation: pointer to the current drag
		drop operation. 
	*/
	virtual void HookDragLeaveEvent(const FDragDropEvent& InDragEvent,UDragDropOperation* InOperation);


	/*
	    Allows derived classes the ability to hook into the parents
		reset event. Called when the main UI (player UI main) is closed/
		out of render.
	*/
	virtual void HookResetEvent();



	/*
	                                     Mutators.
	*/
	void AddToRender();
	void RemoveFromRender();



	/*
	                                    Accessors.
	*/
	FORCEINLINE const ERegionTag& GetRegionTag() const { return RegionTag; }
	UBorder* GetBorder() const;
	USizeBox* GetSizeBox() const;
	UCanvasPanel* GetGroupPanel() const;
	UUIDraggableBase* FindStoredWidget(UItemInstance* AssocaitedInstance) const;
	const bool bIsVisible() const;
};