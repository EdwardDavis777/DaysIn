#pragma once

/*

	 Defines class defaults for equipment slots that are used in the UIPlayerEquipmentMain
	 widget instance.

*/

 
//Other imports.
#include "SharedData/Interaction/ItemEquipTag.h" 
#include "UI/Player/Data/UIEquipSlotData.h"  

 

//Engine imports.
#include "CoreMinimal.h"
#include "UI/Interactables/Abstracts/UIDroppableBase.h"
#include "UIEquipSlotBase.generated.h"



//Forward declares.
class UTextBlock;
class UEquipSlotUIComponent;
class UUIItemIconBase;
class UPlayerEquipmentSubsystem;





UCLASS()
class DAYSIN_API UUIEquipSlotBase : public UUIDroppableBase
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;



	/*
	                           UUIEquipSlotBase components.
	*/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SlotDescription;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUIItemIconBase> ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Configurations")
	EEquipTag EquipTag;



	/*
	                                Custom components.
	*/
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UEquipSlotUIComponent> EquipSlotUIComponent;


	/*
	                                 Cache components.
	*/
	UPROPERTY()
	TObjectPtr<UPlayerEquipmentSubsystem> PlayerEquipmentSubsystem;



	/*
	                                Generic accessors.
	*/

	/*
	    Allows derived classes to access their specific stored item 
		instances through the general stored pointer.

		@tparam UItemInstance: T must be a UItemInstance.

		@return UItemInstance: pointer to an item instance with the 
		class type provided by the caller.
	*/
	template<typename TInstance>
	TInstance* FindAssocaitedInstance()
	{
		if (!SlotData.StoredItem) return nullptr;

		static_assert(TIsDerivedFrom<TInstance, UItemInstance>::IsDerived, "T must be a UItemInstance");
		if (TInstance* Inst = Cast<TInstance>(SlotData.StoredItem))
		{
			return Inst;
		}
		return nullptr;
	}

public:
	UPROPERTY(VisibleAnywhere, Category = "Data|Memory")
	FEquipSlotData SlotData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Configurations")
	FEquipSlotColorData SlotColorData;




	/*
	                                Virtual event functions.
	*/
	virtual void StoreItem(AItemBase* Item, const FIntPoint& Position = FIntPoint(0,0)) override;
	virtual bool StoreDropped(UItemInstance* ItemInstance, const FIntPoint& Position = FIntPoint(0, 0)) override;
	virtual void RemoveStored(TObjectPtr<UItemInstance>& AssocaitedInstance) override;
	

	/*
	                               Virtual hook functions.
	*/
	virtual void HookDragOverEvent(const FGeometry& InGeometry, const FDragDropEvent& InDragEvent, UDragDropOperation* InOperation) override;
	virtual void HookDragLeaveEvent(const FDragDropEvent& InDragEvent, UDragDropOperation* InOperation) override;
	virtual void HookResetEvent() override;


	/*
	                                    Accessors.
	*/
	const EEquipTag GetEquipTag() const;
	const bool& IsOccupied() const;
	UTextBlock* GetDescription() const;
	UUIItemIconBase* GetIcon() const;
};