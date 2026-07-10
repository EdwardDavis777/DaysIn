#pragma once


/*
      Defines class defaults for item run-time instances; each item that implements some sort of logic at 
	  run-time will have a derived instance from this class.
*/
 

 
//Other imports.
#include "Items/Data/ItemRuntimeData.h"
#include "SharedData/Interaction/ItemEquipTag.h" 


//Engine imports.
#include "CoreMinimal.h" 
#include "UObject/NoExportTypes.h" 
#include "ItemInstance.generated.h"
 


//Forward declares.
class UItemDataAsset;
class UUIDraggableBase;
class AItemBase;
class UInstanceUIRuntimeComponent;


UCLASS()
class DAYSIN_API UItemInstance : public UObject
{
	GENERATED_BODY()
public:

	/*
	      Initializes the current item instance with class defaults
		  for run-time events when called.

		  @param WorldContext: pointer to the current world 
		  context.

		  @param ItemData: pointer to the assocaited items static
		  data.
	*/
	virtual void Initialize(UWorld* WorldContext, UItemDataAsset* ItemData);



	/*
	                                  Accessors.
	*/
	TObjectPtr<UItemDataAsset>& GetStaticItemData();
	FItemRunTimeData& GetItemRuntimeData();
	const FIntPoint GetItemSize() const;
	const FIntPoint GetItemUIRotation() const;
	const FIntPoint GetDynamicUISize() const;
	bool bRotated();
	const FText GetUIName() const;
	const EEquipTag GetEquipTag() const;
	const TSubclassOf<AItemBase>& GetItemClass() const;	
	UTexture2D* GetItemIcon();
	TSubclassOf<UUIDraggableBase>& GetIconClass();
	TObjectPtr<UInstanceUIRuntimeComponent>& GetUIRuntimeComponent();

protected:

	/*
	                                    Data.
	*/
	UPROPERTY()
	TObjectPtr<UItemDataAsset> StaticItemData;

	UPROPERTY(SaveGame)
	FItemRunTimeData ItemRuntimeData;

	/*
	                                Custom components.
	*/
	UPROPERTY()
	TObjectPtr<UInstanceUIRuntimeComponent> UIRuntimeComponent;


	/*
							          Components.
	*/
    UPROPERTY()
	TObjectPtr<UWorld> World;


	/*
								  Template accessors.
    */

   /*
		Gets an items data asset with the type passed by the caller.

		@tparam UItemDataAsset: must be type UItemDataAsset or the compiler will
		scream at you!!

		@return UItemDataAsset: returns an item data asset pointer with the class type
		provieded by the caller, if the item instance is assocaited with that type of
		data asset during its construction.
   */
	template<typename TAsset>
	TAsset* GetData()
	{
		if (!StaticItemData) return nullptr;

		static_assert(TIsDerivedFrom<TAsset, UItemDataAsset>::IsDerived, "T must be type UDataAsset");
		TAsset* Asset = CastChecked<TAsset>(StaticItemData);
		return Asset;
	}
};