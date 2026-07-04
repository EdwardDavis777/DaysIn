#pragma once

/*
     Defines weapon instance class defaults for all weapon
	 objects that can be found in the world.
*/
 

//Other imports.
#include "Weapons/Data/WeaponRunTimeData.h"


//Engine imports.
#include "CoreMinimal.h"
#include "Items/Abstracts/ItemInstance.h"
#include "WeaponInstance.generated.h"



//Forward declares.
class UWeaponDataAsset;




UCLASS() 
class DAYSIN_API UWeaponInstance : public UItemInstance
{
	GENERATED_BODY()
	
public:

	/*
	                                    Accessors.
	*/
	TObjectPtr<UWeaponDataAsset>& GetStaticWeaponData();
	FWepRunTimeData& GetRuntimeData();
	FWepRunTimeStats& GetRuntimeStats();

private:
	virtual void Initialize(UWorld* WorldContext, UItemDataAsset* ItemData) override;


	/*
	                          UWeaponInstance data components.
	*/
	UPROPERTY()
	TObjectPtr<UWeaponDataAsset> StaticWeaponData;

	UPROPERTY(SaveGame)
	FWepRunTimeData WeaponRuntimeData;
};