//Engine imports.
#include "UI/Items/SimpleStats/UIWeaponDurability.h"


//Other imports.
#include "Weapons/Abstracts/WeaponInstance.h"
#include "Weapons/Abstracts/WeaponBase.h"


//Custom component imports.
#include "UI/Items/SimpleStats/Components/WeaponDurabilityUIComponent.h"
#include "CustomClasses/Components/Factory/NativeUITemplate.h"





void UUIWeaponDurability::NativeConstruct()
{
	Super::NativeConstruct();
	WeaponDurabilityComponent = NativeUITemplate::CreateDefaultUIComponent<UWeaponDurabilityUIComponent>(GetWorld(), this);
}




/*
								  Initialize functions.
*/

void UUIWeaponDurability::InitializeWeapon(TObjectPtr<UWeaponInstance>& Instance)
{
	if (!Instance) return;

	WeaponDurabilityComponent->CalcualteDurability(Instance->GetRuntimeStats().Durability, DurabilityText);
	WeaponInstance = Instance;
}