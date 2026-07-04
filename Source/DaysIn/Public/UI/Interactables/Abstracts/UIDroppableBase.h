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


//Engine imports.
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIDroppableBase.generated.h"



//Forward declares.
class USizeBox;
class UBorder;
class UCanvasPanel;
class UDroppableUIComponent;
class UUIDraggableSubsystem;
class UPlayerUISubsystem;
class UItemInstance;
class AItemBase;



UCLASS(Abstract)
class DAYSIN_API UUIDroppableBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	void BindDelegates();

	
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
	                                    Custom components.
	*/
	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<UDroppableUIComponent> DroppableComponent;


	/*
	                                     Cache components.
	*/
	UPROPERTY(VisibleAnywhere, Category = "Data|Memory")
	FDroppableRuntimeData Data;

	UPROPERTY()
	TObjectPtr<UUIDraggableSubsystem> DraggableSubsystem;

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


		 @AssocaitedInstance: pointer to an item instance assocaited with some 
		 draggable widget; provided by the dispatch call.
	*/
	void ProxyRemoveEvent(TObjectPtr<UItemInstance>& AssocaitedInstance);



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
    */
	virtual void StoreItem(AItemBase* Item);


	


	/*
	    Handles storing during drop events for draggable widgets through an 
		instance pointer.

		@param ItemInstance: pointer to an item instance
		you wish to store.

		@return TRUE/FLASE: true if the dropped item was stored,
		false if the dropped item faild for some reason.
	*/
	virtual bool StoreDropped(UItemInstance* ItemInstance);



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

		@param InOperation: pointer to the current drag 
		drop operation.
	*/
	virtual void HookDragOverEvent(UDragDropOperation* InOperation);


	/*
	    Allows derived classes to hook into drag leave events from
		the parent. Simply override and implement logic you wish to
		happen during a drag leave event.
	*/
	virtual void HookDragLeaveEvent();


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
	UBorder* GetBorder() const;
	USizeBox* GetSizeBox() const;
	const bool bIsVisible() const;
};