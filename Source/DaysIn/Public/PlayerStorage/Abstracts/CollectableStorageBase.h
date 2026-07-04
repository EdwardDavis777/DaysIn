#pragma once


/*
      Defines class defaults for collectable storage items that can be found
	  in the world. Such as backpacks, shirts with pockets, etc.
*/


//Engine imports.
#include "CoreMinimal.h"
#include "Items/Abstracts/ItemBase.h"
#include "CollectableStorageBase.generated.h"



//Forward declares.
class UCollectableStorageDataAsset;
class UCollectableStorageInstance;



UCLASS()
class DAYSIN_API ACollectableStorageBase : public AItemBase
{
	GENERATED_BODY()
	
protected:

	/*
	                                Data components.
	*/
	UPROPERTY()
	TObjectPtr<UCollectableStorageDataAsset> CollectableStorageDataAsset;

	UPROPERTY()
	TObjectPtr<UCollectableStorageInstance> CollectableStorageInstance;

public:

	/*
	                            Virtual event functions.
	*/
	virtual void Pickup() override;
	virtual void Drop(UItemInstance* Instance) override;



   /*
                                   Engine overrides.
   */
   virtual void PostInitializeComponents() override;
};