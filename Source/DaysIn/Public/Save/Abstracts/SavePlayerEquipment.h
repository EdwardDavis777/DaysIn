#pragma once

/*

      Handles save/load events for the UI player main equipment
	  widget. Loads saved items in equipment slots back into
	  their assocaited slots etc.

*/


//Engine imports.
#include "CoreMinimal.h"
#include "Save/Abstracts/SaveInstanceBase.h"
#include "SavePlayerEquipment.generated.h"


//Forward declares.
class UPlayerUISubsystem;



UCLASS()
class DAYSIN_API USavePlayerEquipment : public USaveInstanceBase
{
	GENERATED_BODY()

private:
	USavePlayerEquipment();

	/*
	                           Cached components.
	*/
	UPROPERTY()
	TObjectPtr<UPlayerUISubsystem> PlayerUISubsystem;



	/*
	                          Load event functions.
	*/

	/*
	     Parses all loaded assets, and adds them back into their
		 assocaited equipment slots.
	*/
	void LoadToSlots();
public:


	/*
	                         Forced event functions.
	*/
	virtual void ProxyInstance(UItemInstance* Instance) override;
	virtual void PostLoadSave(UWorld* WorldContext) override;
};