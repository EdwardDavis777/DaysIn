#pragma once

/*

     Handles the construction of a collectable storage objects
	 inventory widget, etc.
	  
*/


//Engine imports.
#include "CoreMinimal.h"
#include "CustomClasses/Components/GameplayComponent.h"
#include "CollectableStorageUIComponent.generated.h"



//Forward declares.
class UCollectableStorageInstance;
class UUICollectableStorageInventory;
class UPlayerUISubsystem;
class UPlayerEquipmentSubsystem;
class UUIRegionPanel;
class UCanvasPanelSlot;


UCLASS()
class DAYSIN_API UCollectableStorageUIComponent : public UGameplayComponent
{
	GENERATED_BODY()

public:
	virtual void Initialize(UWorld* WorldContext, UObject* OwnerObject) override;
	void BindDelegates();

private:

	/*
	                                Components.
	*/
	UPROPERTY()
	TObjectPtr<UCollectableStorageInstance> StorageInstance;

	UPROPERTY()
	TObjectPtr<UPlayerUISubsystem> PlayerUISubsystem;

	UPROPERTY()
	TObjectPtr<UPlayerEquipmentSubsystem> PlayerEquipmentSubsystem;
	



	/*
	                              Event functions.
	*/



	/*
	      Delegated function; it is broadcasted to whenever a player collects 
		  some storage object in the world. If that collected storage is equal
		  to the storage instance that owns this component, then the function is 
		  executed. It will either construct a brand new inventory instance,
		  or it will re-build a pre-existing inventory instance.

		  @param Instance: pointer to the collected storage
		  instance.
	*/
	void CreateInventory(UCollectableStorageInstance* Instance);



	/*
	     Delegated function; it is broadcated to whenever a player removes/drops
		 some storage object in the world. If that removed storage is equal to 
		 the storage instance that owns this component, then the function is 
		 executed fully. Will simply remove the instance inventory from
		 render.

		 @param Instance: pointer to the removed storage 
		 instance.
	*/
	void DeconstructInventory(UCollectableStorageInstance* Instance);


	/*
	                             Construction events.
	*/

	/*
	     Constructs a brand new inventory instance in memory, and 
		 adds it to a region in the UIPlayerMain. Will also set a
		 run-time flag that will notify other classes about the construction
		 event; dis-allowing re-constructions for the persistent instance.

		 @param Instance: pointer to a storage instance to re-construct
		 an inventory widget for.
	*/
	void ConstructInitial(UCollectableStorageInstance* Instance);

	/*
	     Simply re-builds an already constrcuted inventory widget back into 
		 its assocaited region.
	*/
	void RebuildRegion();



	/*
	                               Helper functions.
	*/

	/*
	     Sets the size of this inventorys parent region to the inventory
		 instance size.

		 @param Instance: pointer to a storage instance
		 object.
	*/
	void SetRegionSize(UCollectableStorageInstance* Instance);


	/*
	                              Runtime components.
	*/
	UPROPERTY()
	TObjectPtr<UUICollectableStorageInventory> StorageInventory;

	UPROPERTY()
	TObjectPtr<UUIRegionPanel> ParentRegion;

	UPROPERTY()
	TObjectPtr<UCanvasPanelSlot> ParentSlot;

	UPROPERTY()
	bool bAlreadyConstructed = false; 
};