#pragma once


/*
     Defines class defaults for saving instance related objects
	 in memory.
*/


//Interface imports.
#include "Save/Interface/SaveClassInterfaces.h"

//Package imports.
#include "Save/Packages/Objects/Abstracts/SPKGInstanceBase.h"



//Engine imports.
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveInstanceBase.generated.h"





UCLASS()
class DAYSIN_API USaveInstanceBase : public USaveGame, public ISaveInterface
{
	GENERATED_BODY()
	
public:
	virtual void Save() override;
	virtual void Load(UWorld* WorldContext) override;


    /*
	                            Cache event functions.
	*/

	/*
	     Caches the provided instance into the proxy cache to prepare it 
		 for serialization during a save event. 

		 @param Instance: pointer to the instance you wish to cache into
		 the save proxy.
	*/
	virtual void ProxyInstance(UItemInstance* Instance) PURE_VIRTUAL(USaveInstanceBase::ProxyInstance, );


	/*
	     Called after this instances assets are loaded fully from a 
		 save slot.

		 @param WorldContext: pointer to the current world
		 context.
	*/
	virtual void PostLoadSave(UWorld* WorldContext) PURE_VIRTUAL(USaveInstanceBase::PostLoadSave, );



	/*
	    UnCaches the provided instance from the proxy cache to ensure that 
		it is not serialized during a save event.

		@param Instance: pointer to the instance you wish to remove from 
		the proxy cache.
	*/
	virtual void UnProxyInstance(UItemInstance* Instance);


protected:
	USaveInstanceBase();


	/*
	                               Components.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FString SaveName;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USaveInstanceBase> LoadedSave;



	/*
	                             Cache components.
	*/
	UPROPERTY()
	TMap<TObjectPtr<UItemInstance>, FSPKGInstanceBase> ProxyCache;
	
	UPROPERTY(SaveGame)
	TArray<FSPKGInstanceBase> SavedPackages;

	UPROPERTY()
	TArray<TObjectPtr<AItemBase>> LoadedAssets;
};