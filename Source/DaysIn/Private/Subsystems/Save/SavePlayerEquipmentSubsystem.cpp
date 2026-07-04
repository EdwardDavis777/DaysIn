//Engine imports.
#include "Subsystems/Save/SavePlayerEquipmentSubsystem.h"


//Other imports.
#include "Save/Abstracts/SavePlayerEquipment.h"




void USavePlayerEquipmentSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	SavePlayerEquipment = MakeSave<USavePlayerEquipment>();
}

void USavePlayerEquipmentSubsystem::Deinitialize()
{
	Super::Deinitialize();
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