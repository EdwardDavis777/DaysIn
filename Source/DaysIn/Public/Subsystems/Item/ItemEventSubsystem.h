#pragma once

/*

      Defines dispatches and caches for runtime item
	  events.

*/


//Other imports.
#include "Dispatches/ItemEventSubsystemDispatches.h"


//Engine imports.
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ItemEventSubsystem.generated.h"




UCLASS()
class DAYSIN_API UItemEventSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	FItemEventSubsystemDelegates Dispatches;
};