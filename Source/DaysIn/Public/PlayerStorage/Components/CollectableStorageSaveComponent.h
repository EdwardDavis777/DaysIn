#pragma once

/* 

      Handles updating storage runtime data that is related 
	  to saving/loading saved items later.

*/


//Engine imports.
#include "CoreMinimal.h"
#include "CustomClasses/Components/GameplayComponent.h"
#include "CollectableStorageSaveComponent.generated.h"


//Forward declares.
class UCollectableStorageInstance;
class UStorageInventorySubsystem;
class UItemInstance;
struct FSPKGSubInstance;


UCLASS()
class DAYSIN_API UCollectableStorageSaveComponent : public UGameplayComponent
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(UWorld* WorldContext, UObject* OwnerObject) override;
	void BindDelegates();

    

	/*
	                              Load event functions.
	*/

	/*
	       Simply loads all saved stored items when the game
		   starts, and clears the inner items array after all items 
		   have been reloaded.

		   @param InnerItems: map of deserialized actor pointers, and 
		   their assocaited save package.

	*/
	void LoadSavedObjects(TMap<TObjectPtr<AActor>, FSPKGSubInstance>& InnerItems);


	/*
	                              Runtime cache functions.
	*/

	/*
	     Caches the added instance, and position into the sub instances 
		 cache for save events later.

		 @param AssocaitedStorage: pointer to the assocaited storage
		 instance, not actually used here, but needed for the dispatch signature.

		 @param AddedInstance: pointer to the added 
		 instance.

		 @param Position: reference to the 2D position that the instance
		 was added to.
	*/
	void AddSubInstance(UObject* AssocaitedStorage, UObject* AddedInstance, const FIntPoint& Position);


	/*
	     Removes the passed instances from the sub instances cache 
		 if it is found.

		 @param AssocaitedStorage: pointer to the assocaited storage
		 instance, not actually used here, but needed for the dispatch signature.

		 @param RemovedInstance: pointer to the removed
		 instance.
	*/
	void RemoveSubInstance(UObject* AssocaitedStorage, UObject* RemovedInstance);

private:


	/*
	                             Components.
	*/
	UPROPERTY()
	TObjectPtr<UCollectableStorageInstance> StorageInstance;

	UPROPERTY()
	TObjectPtr<UStorageInventorySubsystem> InventorySubsystem;
};