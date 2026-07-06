#pragma once

/*
     Defines class defaults for equipment slots that hold external
	 storages, such as backpacks, etc.
*/

 
//Engine imports.
#include "CoreMinimal.h"
#include "UI/Player/UIEquipSlotBase.h"
#include "UIStorageSlot.generated.h"



//Forward declares.
class UCollectableStorageInstance;



UCLASS()
class DAYSIN_API UUIStorageSlot : public UUIEquipSlotBase
{
	GENERATED_BODY()

public:
	
	/*
								 Virtual event functions.
	*/
	virtual void StoreItem(AItemBase* Item, const FIntPoint& Position = FIntPoint(0, 0)) override;
	virtual bool StoreDropped(UItemInstance* ItemInstance) override;
	virtual void RemoveStored(TObjectPtr<UItemInstance>& AssocaitedInstance) override;

private:


	/*
	                                  Components.   
	*/
	UPROPERTY()
	TObjectPtr<UCollectableStorageInstance> CollectableStorageInstance;
};