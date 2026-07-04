//Engine imports.
#include "Subsystems/Player/PlayerUISubsystem.h"


 
void UPlayerUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection); 
}
 

void UPlayerUISubsystem::Deinitialize()
{
	Super::Deinitialize();
}



/*
									   Mutators.
*/

void UPlayerUISubsystem::SetPlayerMain(UUIPlayerMain* UIMain)
{
	if (!UIMain) return;
	PlayerMain = UIMain;
}

void UPlayerUISubsystem::SetPlayerEquipmentMain(UUIPlayerEquipmentMain* UIEquipment)
{
	if (!UIEquipment) return;
	PlayerEquipmentMain = UIEquipment;
}



/*
									  Accessors.
*/

UUIPlayerMain* UPlayerUISubsystem::GetPlayerMain() const
{
	return PlayerMain.Get();
}

 UUIPlayerEquipmentMain* UPlayerUISubsystem:: GetEquipmentMain() const
{
	return PlayerEquipmentMain.Get();
}