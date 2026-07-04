#pragma once


/*
    Global subsystem for all draggable widget instances
	in user interfaces.
*/


//Other imports.
#include "Dispatches/UIDraggableSubsystemDispatches.h"


//Engine imports.
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UIDraggableSubsystem.generated.h"





UCLASS()
class DAYSIN_API UUIDraggableSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;


public:
	FDraggableDispatches DraggableDispatches;
};