//Engine imports.
#include "Subsystems/Save/SavePlayerEquipmentSubsystem.h"



//Other imports.
#include "Save/Abstracts/SavePlayerEquipment.h"

//Subsystem imports.
#include "Subsystems/Player/PlayerUISubsystem.h"




void USavePlayerEquipmentSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	SavePlayerEquipment = MakeSave<USavePlayerEquipment>();
	BindDelegates();
}


void USavePlayerEquipmentSubsystem::Deinitialize()
{
	Super::Deinitialize();
}


void USavePlayerEquipmentSubsystem::BindDelegates()
{
	if (!PlayerUISubsystem) return;
	PlayerUISubsystem->PlayerUISubsystemDispatches.UIEquipmentMainInitialized.AddUObject(this, &USavePlayerEquipmentSubsystem::LoadOnStart);
}



/*
                                  Save event functions.
*/

void USavePlayerEquipmentSubsystem::SaveEquipment(UItemInstance* Instance)
{
	if (!Instance) return;
	SavePlayerEquipment->ProxyInstance(Instance);
}

void USavePlayerEquipmentSubsystem::UnSaveEquipment(UItemInstance* Instance)
{
	if (!Instance) return;
	SavePlayerEquipment->UnProxyInstance(Instance);
}


/*
							      Load event functions.
*/

void USavePlayerEquipmentSubsystem::LoadOnStart()
{
	if (!SavePlayerEquipment) return;
	LoadSaveAtBegin(SavePlayerEquipment);
}