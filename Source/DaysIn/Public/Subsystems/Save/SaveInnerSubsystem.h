#pragma once

/*

      Used for the deserialization of recursive instances after a base
	  object has already been loaded. Manages dependency loading, and 
	  boot strapping.

*/


//Engine imports.
#include "CoreMinimal.h"
#include "Subsystems/Save/SaveSubsystem.h"
#include "SaveInnerSubsystem.generated.h"



//Forward declares.
class USaveGenericInner;
struct FSPKGSubInstance;
class UItemInstance;


UCLASS()
class DAYSIN_API USaveInnerSubsystem : public USaveSubsystem
{
	GENERATED_BODY()

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	void BindDelegates();


	/*
	                                  Components.
	*/
	UPROPERTY()
	TObjectPtr<USaveGenericInner> SaveGenericInner;


	/*
	                            Save inner event functions.
	*/


	/*
	     Called after an outer object has been fully deserialized, begins
		 deserialization of inner sub object packages/attributes.

		 @param SavePackages: array of references to inner save 
		 packages.


		 @param SentBackInners: map of AActor pointers and their assocaited
		 save packages that will be populated during a deserialize event of inner actors/instances.

		 @param OuterInstance: pointer to the outer 
		 instance.
	*/
	void PostOuterDeserialization(const TArray<FSPKGSubInstance>& SavePackages, TMap<TObjectPtr<AActor>, FSPKGSubInstance>& SentBackInners,UItemInstance* OuterInstance);
};