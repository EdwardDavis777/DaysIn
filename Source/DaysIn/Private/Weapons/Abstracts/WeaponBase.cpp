//Engine imports.
#include "Weapons/Abstracts/WeaponBase.h"

//Component imports.
#include "Components/SphereComponent.h"


//Other imports.
#include "Weapons/Data/WeaponDataAsset.h" 
#include "Weapons/Abstracts/WeaponInstance.h"
 

//Custom component imports.
#include "Items/Components/ItemPhysicsComponent.h"



AWeaponBase::AWeaponBase()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMeshComponent"));
	WeaponMesh->SetupAttachment(RootComponent);
} 


void AWeaponBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ItemDataAsset)
	{
		WeaponDataAsset = GetData<UWeaponDataAsset>();
		WeaponInstance = GetInstance<UWeaponInstance>();
	}
}


/*
							   Interface event functions.
*/

void AWeaponBase::Pickup()
{
	Super::Pickup();
	Destroy();
}


void AWeaponBase::Drop(UItemInstance* Instance)
{
	Super::Drop(Instance);

	if (auto* WepInst = GetInstance<UWeaponInstance>())
	{
		WeaponDataAsset = WepInst->GetStaticWeaponData();
		WeaponInstance = WepInst;
		ItemPhysicsComponent->ApplyCollisionAndPhysicsButIgnorePawn(WeaponMesh, WeaponDataAsset->ItemPhysicsProperties);
	}
}