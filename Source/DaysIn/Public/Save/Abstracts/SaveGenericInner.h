#pragma once

/*

       Handles deserialization events for generic inner 
	   objects.

*/


//Engine imports.
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGenericInner.generated.h"


//Forward declares.
struct FSPKGSubInstance;
class UItemInstance;



UCLASS()
class DAYSIN_API USaveGenericInner : public USaveGame
{
	GENERATED_BODY()
  
private:

	/*
	                                   Components.
	*/
	UPROPERTY()
	FString SaveName = "InnerSave";
public:

	/*
	                               Load event functions.
	*/

	/*
	      Spawns empty items, deserializes the passed save packges, and returns them back to
		  the outer instance for repacking events. Note this function is recursive
		  meaning it will continue to deserialize an inners, inner sub instances.

		  @param SavePackages: array of references to the save 
		  packages to deserailize from.

		 @param SentBackInners: map of AActor pointers and their assocaited
		 save packages that will be sent back to the outer instance.

		  @param OuterInstance: pointer to the owner/outer 
		  instance.

		  @param WorldContext: pointer to the current world
		  context.
	*/
	void DeserializeInners(const TArray<FSPKGSubInstance>& SavePackages, TMap<TObjectPtr<AActor>, FSPKGSubInstance>& SentBackInners,UItemInstance* OuterInstance,UWorld* WorldContext);
};