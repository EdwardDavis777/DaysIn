#pragma once


/*

     Defines class defaults for all item objects that can be found
	 in the world.

	 Note: this item class only implements a default for a static mesh,
	 if you have an item that needs a skeletal mesh, like a weapon or 
	 something, you must specify that in the derived class components
	 tree.
	   
*/


//Interface imports.
#include "Interfaces/Item/ItemInterfaceClass.h"


//Other imports.
#include "Items/Data/Abstracts/ItemDataAsset.h"
#include "Items/Abstracts/ItemInstance.h"


//Engine imports.
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"



//Forward declares.
class USphereComponent;
class UItemPhysicsComponent;
class UItemEventSubsystem;


UCLASS()
class DAYSIN_API AItemBase : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
protected:	
	AItemBase();



	/*
	                              AItemBase components.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<USphereComponent> CollisionSphere;
	



	/*
	                            AItemBase data components.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UItemDataAsset> ItemDataAsset;
    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data| Memory")
	TObjectPtr<UItemInstance> ItemInstance;


	/*
	                              Custom components.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component") 
	TObjectPtr<UItemPhysicsComponent> ItemPhysicsComponent;


	/*
	                              Cached components.
	*/
	UPROPERTY()
	TObjectPtr<UItemEventSubsystem> ItemEventSubsystem;

public:
	 
	/* 
	                           Interface event functions.
	*/

	/*
	     Called when an item is picked-up by a player character
		 at runtime.
	*/
	virtual void Pickup() override;



	/*
	     Called when an item is dropped by a player character 
		 at runtime.

		 @param Instance: pointer to the dropped items 
		 runtime instance.
	*/
	virtual void Drop(UItemInstance* Instance) override;



	/*
	                             Templated accessors.
	*/

	/*
	     Gets an items data asset with the type passed by the 
		 caller.

		 @tparam UItemDataAsset: must be type UItemDataAsset or the compiler will 
		 scream at you!!

		 @return UItemDataAsset: returns an item data asset pointer with the class type
		 provieded by the caller, if the item is assocaited with that type of 
		 data asset.
	*/
	template<typename TAsset>
	TAsset* GetData()
	{
		if (!ItemDataAsset) return nullptr;

		static_assert(TIsDerivedFrom<TAsset, UItemDataAsset>::IsDerived, "T must be type UItemDataAsset");
		TAsset* Asset = Cast<TAsset>(ItemDataAsset);
		return Asset;
	}

	/*
	    Gets an items instance with the class type passed by the 
		caller.

		@tparm UItemInstance: T must be type UItemInstance.

		@return UItemInstance: returns an item instance pointer with the class
		type provided by the caller if the item is assocaited with that
		type of instance.

	*/
	template<typename TInstance>
	TInstance* GetInstance()
	{
		if (!ItemInstance) return nullptr;

		static_assert(TIsDerivedFrom<TInstance, UItemInstance>::IsDerived, "T must be type UItemInstance");
		TInstance* Instance = Cast<TInstance>(ItemInstance);
		return Instance;
	}

	/*
	                                  Accessors.
	*/
	UItemInstance* Instance();
	const EEquipTag GetEquipTag() const;


	/*
	                               Engine overrides.
	*/
	virtual void PostInitializeComponents() override;
};