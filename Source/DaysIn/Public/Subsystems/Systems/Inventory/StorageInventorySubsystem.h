#pragma once


//Other imports.
#include "Dispatches/StorageInventoryDispatches.h"


//Engine imports.
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "StorageInventorySubsystem.generated.h"



UCLASS()
class DAYSIN_API UStorageInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	FStorageInventoryDelegates StorageDispatches;

};
