//Engine imports.
#include "Subsystems/Player/PlayerEquipmentSubsystem.h"




void UPlayerEquipmentSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	BindDelegates();
}
 
void UPlayerEquipmentSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UPlayerEquipmentSubsystem::BindDelegates()
{
	PlayerEquipmentDispatches.StorageAdded.AddUObject(this, &UPlayerEquipmentSubsystem::AddStorage);
	PlayerEquipmentDispatches.StorageRemoved.AddUObject(this, &UPlayerEquipmentSubsystem::RemoveStorage);
}



/*
						      Equipment event functions.
*/

void UPlayerEquipmentSubsystem::AddStorage(UCollectableStorageInstance* Storage)
{
	if (!Storage) return;
	if (!PlayerStorages.Contains(Storage)) { PlayerStorages.Emplace(Storage); }
}

void UPlayerEquipmentSubsystem::RemoveStorage(UCollectableStorageInstance* Storage)
{
	if (!Storage) return;
	if (PlayerStorages.Contains(Storage)) { PlayerStorages.Remove(Storage); }
}



/*
								     Accessors.
*/

const TArray<TObjectPtr<UCollectableStorageInstance>>& UPlayerEquipmentSubsystem::GetPlayerStorages() const
{
	return PlayerStorages;
}