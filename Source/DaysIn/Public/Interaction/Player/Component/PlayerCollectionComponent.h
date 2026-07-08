#pragma once

/*

     Performs checks at run-time to determine how items will be 
	 stored/collected by the player character. 

*/


//Engine imports. 
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCollectionComponent.generated.h"



//Forward declares.
class UPlayerSubsystem;
class UPlayerUISubsystem;
class UPlayerEquipmentSubsystem;
class AItemBase;


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DAYSIN_API UPlayerCollectionComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	/*
	    Binds component functions to system 
		dispatches.
	*/
	void BindDelegates();

	/*
	                        UPlayerCollectionComponent components.
	*/
	UPROPERTY()
	TObjectPtr<UPlayerSubsystem> PlayerSubsystem;

	UPROPERTY()
	TObjectPtr<UPlayerUISubsystem> PlayerUISubsystem;

	UPROPERTY()
	TObjectPtr<UPlayerEquipmentSubsystem> PlayerEquipmentSubsystem;


	/*
	                            Collection event functions.
	*/


	/*
	    Parses all player storage methods, and calls an associated store
		function to the first available storage object that can store the item
		then returns.

		@param Item: pointer to the current item you wish 
		to try to collect.
	*/
	void OnCollection(AItemBase* Item);
	


	/*
	                              Engine overrides.
	*/
	virtual void BeginPlay() override;
};