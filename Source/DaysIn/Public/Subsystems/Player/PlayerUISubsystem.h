#pragma once


/*
    Handles player UI related events, and data for global 
	access across classes.
*/
 
 
//Other imports.
#include "Dispatches/PlayerUISubsystemDispatches.h"  


//Engine imports.  
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerUISubsystem.generated.h"



//Forward declares.
class UUIPlayerMain;
class UUIPlayerEquipmentMain;



UCLASS()
class DAYSIN_API UPlayerUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/*
	                               Cache components.
	*/
	UPROPERTY()
	TObjectPtr<UUIPlayerMain> PlayerMain;

	UPROPERTY()
	TObjectPtr<UUIPlayerEquipmentMain> PlayerEquipmentMain;


public:
	 FPlayerUISubsystemDelegates PlayerUISubsystemDispatches;


	/*
	                                   Mutators.
	*/



	/*
	     Updates the PlayerUISubsystem with the current UIMain 
		 pointer.

		 @param UIMain: pointer to the current UIPlayerMain widget
		 instance.
	*/
	void SetPlayerMain(UUIPlayerMain* UIMain);
	


	/*
	    Updates the PlayerUISubsystem with the current UIEquipment
		pointer.

		@param UIEquipment: pointer to the current UUIPlayerEquipmentMain
		widget instance.
	*/
	void SetPlayerEquipmentMain(UUIPlayerEquipmentMain* UIEquipment);


	/*
	                                  Accessors.
	*/
	UUIPlayerMain* GetPlayerMain() const;
	UUIPlayerEquipmentMain* GetEquipmentMain() const;
};