//Engine imports.
#include "Subsystems/Save/SaveSubsystem.h"


//Subsystem imports.
#include "Subsystems/Player/PlayerUISubsystem.h"
#include "Subsystems/Player/PlayerEquipmentSubsystem.h"



 
void USaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	SaveManager = Collection.InitializeDependency<USaveManagerSubsystem>();
	PlayerUISubsystem = Collection.InitializeDependency<UPlayerUISubsystem>();
	PlayerEquipmentSubsystem = Collection.InitializeDependency<UPlayerEquipmentSubsystem>();
}


void USaveSubsystem::Deinitialize()
{
	Super::Deinitialize();
}


/*
								   Load event functions.
*/

void USaveSubsystem::LoadSaveAtBegin(USaveGame* SaveClass)
{
	if (!SaveClass || !SaveManager) return;
	SaveManager->Load(SaveClass,GetWorld());
}