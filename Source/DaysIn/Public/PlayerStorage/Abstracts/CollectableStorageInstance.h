#pragma once

/*
     Defines class defaults for the run-time instance for collectable storage 
	 objects.
*/


//Engine imports.
#include "CoreMinimal.h" 
#include "Items/Abstracts/ItemInstance.h"
#include "CollectableStorageInstance.generated.h"



//Forward decalres.
class UItemDataAsset;
class UCollectableStorageDataAsset;
class UCollectableStorageUIComponent;
class UUICollectableStorageInventory;
class UStorageInventoryComponent;




UCLASS()
class DAYSIN_API UCollectableStorageInstance : public UItemInstance
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(UWorld* WorldContext, UItemDataAsset* ItemData) override;



	/*
	                                     Accessors.
	*/
	TObjectPtr<UCollectableStorageDataAsset>& GetStaticStorageData();
	TObjectPtr<UCollectableStorageUIComponent>& GetStorageUIComponent();
	TObjectPtr<UStorageInventoryComponent>& GetInventoryComponent();
	TSubclassOf<UUICollectableStorageInventory>& GetInventoryClass();
	const FIntPoint& GetSize() const;

private:


	/*
	                                   Data components.
	*/
	UPROPERTY()
	TObjectPtr<UCollectableStorageDataAsset> StaticStorageData;



	/*
	                                 Custom components.
	*/
	UPROPERTY(VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCollectableStorageUIComponent> CollectableStorageUIComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStorageInventoryComponent> StorageInventoryComponent;
};