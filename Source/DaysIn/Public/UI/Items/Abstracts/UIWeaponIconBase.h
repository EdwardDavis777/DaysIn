#pragma once

/*
    Defines class defaults for all weapon icons that are used 
	in user interfaces.
*/


//Engine imports.
#include "CoreMinimal.h"
#include "UI/Items/Abstracts/UIItemIconBase.h"
#include "UIWeaponIconBase.generated.h"



//Forward declares.
class UUIWeaponDurability;
class UWeaponInstance;



UCLASS(Abstract)
class DAYSIN_API UUIWeaponIconBase : public UUIItemIconBase
{
	GENERATED_BODY()

public:
	virtual void Init(UItemInstance* Instance) override;
	virtual void Init(AItemBase* RawItem) override;

private:


	/*
	                    UUIWeaponSlotBase components.
	*/
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UUIWeaponDurability> WeaponDurability;


	/*
	                         Cache components.
	*/
	UPROPERTY()
	TObjectPtr<UWeaponInstance> WeaponInstance;
};