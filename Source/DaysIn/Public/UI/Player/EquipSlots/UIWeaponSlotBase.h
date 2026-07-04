#pragma once



/*
     Base class for all weapon slots that are inside of the players
	 UIEquipmentMain widget.
*/


//Engine imports.
#include "CoreMinimal.h"
#include "UI/Player/UIEquipSlotBase.h"
#include "UIWeaponSlotBase.generated.h" 
 


//Forward declares.
class UWeaponInstance;


UCLASS()
class DAYSIN_API UUIWeaponSlotBase : public UUIEquipSlotBase
{
	GENERATED_BODY()
	
private:

	/*
	                               Cached components.  
	*/
	UPROPERTY(VisibleAnywhere, Category = "Data|Memory", meta = (AllowPrivateAccess = true))
	TObjectPtr<UWeaponInstance> StoredWeapon;
public:

	/*
	                             Virtual event functions.
	*/
	virtual void StoreItem(AItemBase* Item) override;
	virtual bool StoreDropped(UItemInstance* ItemInstance) override;
	virtual void RemoveStored(TObjectPtr<UItemInstance>& AssociatedInstance) override;
};