//Engine imports.
#include "Subsystems/Save/SaveSubsystem.h"

//Utility imports.
#include "SubsystemUtilitys/SubsystemUtility.h"



void USaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Collection.InitializeDependency<USaveManagerSubsystem>();
	SaveManager = SubUtility::FindSub<USaveManagerSubsystem>(GetWorld());
}

void USaveSubsystem::Deinitialize()
{
	Super::Deinitialize();
}