#pragma once

/*
     Holds global player equipment data, this subsystem is updated
	 by classes at run-time.
*/


//Other imports.
#include "Dispatches/PlayerEquipmentDispatches.h"


//Engine imports.
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerEquipmentSubsystem.generated.h" 




//Forward declares.
class UCollectableStorageInstance;




UCLASS()
class DAYSIN_API UPlayerEquipmentSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	void BindDelegates();


	/*
	                               Cached data.
	*/
	UPROPERTY()
  	TArray<TObjectPtr<UCollectableStorageInstance>> PlayerStorages;

	 

	/*
	                        Equipment event functions.
	*/

	/*
		 Adds the passed storage pointer to the subsystems external
		 player storage cache.

		 @param Storage: pointer to the storage you wish to
		 cache.
	*/
	void AddStorage(UCollectableStorageInstance* Storage);


	/*
		Removes the passed storage pointer from the subsystems external
		player storage cache.

		@param Storage: pointer to the storage you wish to remove
		from the subsystem cache.
	*/
	void RemoveStorage(UCollectableStorageInstance* Storage);



public:
	FPlayerEquipmentDelegates PlayerEquipmentDispatches;


	/*
	                              Accessors.
	*/
	const TArray<TObjectPtr<UCollectableStorageInstance>>& GetPlayerStorages() const;
};