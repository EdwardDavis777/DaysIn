#pragma once

/*
   
     Creates a save class instance for updating the equipment player save 
	 class at run-time for possible savable items.

*/



//Engine imports.
#include "CoreMinimal.h"
#include "Subsystems/Save/SaveSubsystem.h"
#include "SavePlayerEquipmentSubsystem.generated.h"



//Forward declares.
class USavePlayerEquipment;
class UItemInstance;



UCLASS()
class DAYSIN_API USavePlayerEquipmentSubsystem : public USaveSubsystem
{
	GENERATED_BODY()
	
private:
   
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;


	/*
	                             Components.
	*/
	UPROPERTY()
	TObjectPtr<USavePlayerEquipment> SavePlayerEquipment;


public:


	/*
	                          Save event functions.
	*/
	void SaveEquipment(UItemInstance* Instance);
	void UnSaveEquipment(UItemInstance* Instance);
};