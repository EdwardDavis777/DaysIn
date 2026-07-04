#pragma once

/*
     Defines run-time logic for UIEquipSlot widget 
	 instances.
*/





//Engine imports.
#include "CoreMinimal.h"
#include "CustomClasses/Components/NativeUIComponent.h"
#include "EquipSlotUIComponent.generated.h"

 
//Forward declares.
class UUIEquipSlotBase;
class AItemBase;
class UUIItemIconBase;
class UItemInstance;
class UDragDropOperation;
class USavePlayerEquipmentSubsystem;



UCLASS()
class DAYSIN_API UEquipSlotUIComponent : public UNativeUIComponent
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(UWorld* WorldContext, UUserWidget* OwnerWidget) override;
   

	/*
	                           Equipment slot event functions.
	*/

	
	
	/*
	     Handles store events for an equipment slot; will display the item instances
		 icon onto the slots icon place holder, and collapse the slot description. 
		 Will then store a pointer to the passed item instance to the instance cache.

		 @param Instance: pointer to the item to store
		 instance. 

		 @param Icon: pointer to the icon assocaited
		 with this slot.

		 @param InstanceCache: pointer to the item instance
		 cache.
	*/
	void HandleStore(UItemInstance* Instance, UUIItemIconBase* Icon,TObjectPtr<UItemInstance>& InstanceCache);



	
	/*
	    Handles remove events for this equipment slot, will simply remove the item icon from dispaly,
		and display is description in place. Also will clear the cached stored item from memory.

		@param AssocaitedInstance: pointer to the item instance
		being removed.

		@param InstanceCache: pointer to the stored item 
		in this slot.

		@param Icon: pointer to the item icon stored in
		this slot.
	*/
	void HandleRemove(TObjectPtr<UItemInstance>& AssocaitedInstance, TObjectPtr<UItemInstance>& InstanceCache, UUIItemIconBase* Icon);

	
	
	/*
	    Handles mouse hover over events; checks if the hovered item can be stored inside
		of this slot, if so it will toggle the slots color to a can place color, if false, 
		it will simply do nothing.

		@param InOperation: pointer to the current drag drop
		operation.

		@param CanPlaceColor: reference to the color you wish to set the 
		border to if the item can be placed in this slot.
	*/
	void HandleHoverOver(UDragDropOperation* InOperation,const FLinearColor& CanPlaceColor);



	/*
	    Resets this equip slot to its default border color
		when called.

		@param DefaultBorderColor: reference to the default border
        color of this slot.
	*/
	void ResetBorder(const FLinearColor& DefaultBorderColor);


	/*
	     Collapses the equip slots description and displays the item icon
		 that is stored inside of the slot.

		 @param Icon: pointer to the stored item 
		 icon in the slot.
	*/
	void CollapseDescription(UUIItemIconBase* Icon);




	/*
	     Uncollapses the equip slots description and removes the item icon
		 from render in the equipment slot.

		 @param Icon: pointer to the stored item
		 icon in the slot.
	*/
	void UnCollapseDescription(UUIItemIconBase* Icon);


	/*
	                                 Helper functions.
	*/

	/*
	   Checks if an item instance can be stored in this equip slot.

	   @param ItemInstance: pointer to the item instance you wish to 
	   check.

	   @return TRUE/FALSE: true if the item instance can be stored inside of 
	   this equipment slot. False if it cannot be stored.
	*/
	bool bCanStore(UItemInstance* ItemInstance);


private:

	/*
	                          UEquipSlotUIComponent components.
	*/
	UPROPERTY()
	TObjectPtr<UUIEquipSlotBase> EquipSlot;

	UPROPERTY()
	TObjectPtr<USavePlayerEquipmentSubsystem> SaveEquipmentSubsystem;
};